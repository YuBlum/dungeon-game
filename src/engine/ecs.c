#include <string.h>
#include "engine/types.h"
#include "engine/ecs.h"
#include "engine/hashtable.h"
#include "engine/list.h"
#include "general/core.h"

typedef u32 ComponentID, ArchetypeID;

#define COMP_NOID ((ComponentID)-1)

typedef union {
  struct {
    ArchetypeID archetype;
    Entity entity;
  };
  EntityReference reference;
} EntityReferenceInternal;

typedef struct {
  u32 index;
  SystemEvent event;
} SystemID;

typedef struct {
  const char **component_names;
  ComponentID *component_id;
  void  **component_buffs;
  usize *component_sizes;
  usize component_amount;
  usize not_empty_component_amount;
  usize entities_amount;
  bool *entity_is_last_frame;
  bool *entity_is_first_frame;
  void ***entity_insert_component_data;
  const char ***entity_insert_component;
  const char ***entity_remove_component;
  usize entity_requested_remove_component_amount;
  usize entity_requested_insert_component_amount;
  u32  entity_requested_create_amount;
  bool entity_requested_destroy;
  void *entity_creation_queue;
  usize entity_size;
  EntityReferenceInternal ***entity_references;
  ArchetypeID id;
} Archetype;

typedef struct {
  ArchetypeID *archetypes;
  usize size;
} Component;

typedef struct {
  SystemFn fn;
  bool active;
  bool paused;
  const char **must_have;
  const char **must_not_have;
#if DEVMODE
  const char *creation_file;
  u32 creation_line;
#endif
} System;

typedef struct {
  Component *components;
  Archetype *archetypes;
  System  *systems[SYSTEM_EVENTS_AMOUNT];
  SystemID *system_ids;
  Archetype **archetype_queue;
  Archetype *archetype_cur;
  Archetype *archetype_creation;
  usize entities_amount;
  bool on_entity_creation;
  bool on_system;
  const char **temp_comps_names;
} World;

static World world;

#if DEVMODE
static const char *system_event_str[] = {
  "ON_SCENE_START",
  "ON_SCENE_END",
  "ON_PRE_UPDATE",
  "ON_UPDATE",
  "ON_POS_UPDATE",
  "ON_PRE_DRAW_GAME",
  "ON_DRAW_GAME",
  "ON_POS_DRAW_GAME",
  "ON_PRE_DRAW_UI",
  "ON_DRAW_UI",
  "ON_POS_DRAW_UI",
  "ON_PRE_DRAW_SCREEN",
  "ON_DRAW_SCREEN",
  "ON_POS_DRAW_SCREEN",
  "ON_CREATE",
  "ON_DESTROY",
};
_Static_assert(sizeof (system_event_str) / sizeof (char *) == SYSTEM_EVENTS_AMOUNT, "system_event_str doesn't handle all system events");
#endif

void
ecs_create(void) {
#if DEVMODE
  (void)system_event_str;
#endif
  world.components = hashtable_create(sizeof (Component));
  world.system_ids = hashtable_create(sizeof (SystemID));
  for (SystemEvent event = 0; event < SYSTEM_EVENTS_AMOUNT; event++) {
    world.systems[event] = list_create(sizeof (System));
  }
  world.archetypes = list_create(sizeof (Archetype));
  world.archetype_queue = list_create(sizeof (Archetype *));
  world.temp_comps_names = list_create(sizeof (const char *));
  world.archetype_cur = 0;
  world.on_entity_creation = false;
  world.on_system = false;
}

void
__ecs_component_create(usize size, const char *name, const char *file, u32 line) {
#if DEVMODE
  if (hashtable_has(world.components, name)) ERROR("%s:%u: '%s' component already exists", file, line, name);
#endif
  Component comp = { .archetypes = list_create(sizeof (ArchetypeID)), .size = size };
  hashtable_insert(world.components, name, comp);
}

static Archetype *
ecs_find_archetype(usize comps_amount, const char *comps_names[comps_amount], const char *file, u32 line) {
#if DEVMODE
  for (u32 i = 0; i < comps_amount; i++) {
    if (!hashtable_has(world.components, comps_names[i])) ERROR("%s:%u: '%s' component doesn't exists", file, line, comps_names[i]);
  }
#endif
  /* check for existing archetype */
  Archetype *archetype = 0;
  Component *comp = hashtable_get_address(world.components, comps_names[0]);
  for (usize i = 0; i < list_size(comp->archetypes); i++) {
    if (world.archetypes[comp->archetypes[i]].component_amount != comps_amount) continue;
    Archetype *archetype_test = &world.archetypes[comp->archetypes[i]];
    for (usize j = 1; j < comps_amount; j++) {
      if (!hashtable_has(archetype_test->component_id, comps_names[j])) {
        archetype_test = 0;
        break;
      }
    }
    if (archetype_test) {
      archetype = archetype_test;
      break;
    }
  }
  /* if an archetype doesn't exists create it */
  if (!archetype) {
    u32 archetype_id = list_size(world.archetypes);
    list_grow(world.archetypes);
    archetype = &world.archetypes[archetype_id];
    archetype->id = archetype_id;
    archetype->component_names = list_create(sizeof (const char *));
    archetype->component_sizes = list_create(sizeof (usize));
    archetype->component_buffs = list_create(sizeof (void *));
    archetype->component_id = hashtable_create(sizeof (ComponentID));
    archetype->component_amount = 0;
    archetype->not_empty_component_amount = 0;
    archetype->entities_amount = 0;
    archetype->entity_size = 0;
    for (usize i = 0; i < comps_amount; i++) {
      Component *comp = hashtable_get_address(world.components, comps_names[i]);
      list_push(comp->archetypes, archetype->id);
      ComponentID id = COMP_NOID;
      if (comp->size != 0) {
        id = archetype->not_empty_component_amount++;
        list_push(archetype->component_sizes, comp->size);
        list_push(archetype->component_buffs, list_create(comp->size));
        archetype->entity_size += comp->size;
      }
      hashtable_insert(archetype->component_id, comps_names[i], id);
      list_push(archetype->component_names, comps_names[i]);
      archetype->component_amount++;
    }
    archetype->entity_creation_queue = list_create(archetype->entity_size);
    archetype->entity_is_last_frame  = list_create(sizeof (bool));
    archetype->entity_is_first_frame = list_create(sizeof (bool));
    archetype->entity_references = list_create(sizeof (EntityReferenceInternal **));
    archetype->entity_insert_component_data = list_create(sizeof (void **));
    archetype->entity_insert_component = list_create(sizeof (const char **));
    archetype->entity_remove_component = list_create(sizeof (const char **));
    archetype->entity_requested_destroy = false;
    archetype->entity_requested_create_amount = 0;
    archetype->entity_requested_insert_component_amount = 0;
    archetype->entity_requested_remove_component_amount = 0;
  }
  return archetype;
}

void
__ecs_entity_creation_begin(usize comps_amount, const char *comps_names[comps_amount], const char *file, u32 line) {
#if DEVMODE
  if (world.on_entity_creation) ERROR("%s:%u: Trying to start an entity creation with another already happening.", file, line);
  if (comps_amount == 0) ERROR("%s:%u: Trying to start an entity creation without components", file, line);
#endif
  world.on_entity_creation = true;
  Archetype *archetype = ecs_find_archetype(comps_amount, comps_names, file, line);
  world.archetype_creation = archetype;
  list_grow(archetype->entity_creation_queue);
  list_push(archetype->entity_references, list_create(sizeof (EntityReferenceInternal *)));
}

void
__ecs_entity_creation_get_reference(EntityReference *reference, const char *file, u32 line) {
#if DEVMODE
  if (!world.on_entity_creation) ERROR("%s:%u: Trying to get reference of a entity on creation outside of an entity creation.", file, line);
  if (!reference) ERROR("%s:%u: Expected pointer to an entity reference, but got NULL", file, line);
  if ((*reference) != 0) ERROR("%s:%u: entity reference is already referecing an entity, please use 'ecs_entity_clean_reference' before calling this function", file, line);
#endif
  Archetype *archetype = world.archetype_creation;
  EntityReferenceInternal *ref = (EntityReferenceInternal *)reference;
  ref->archetype = archetype->id + 1;
  ref->entity = list_size(archetype->entity_references);
  list_push(archetype->entity_references[ref->entity - 1], ref);
}

void *
__ecs_entity_creation_setup_component(const char *comp_name, const char *file, u32 line) {
  Archetype *archetype = world.archetype_creation;
#if DEVMODE
  if (!world.on_entity_creation) ERROR("%s:%u: Trying to setup a component outside of an entity creation.", file, line);
  if (!hashtable_has(world.components, comp_name)) ERROR("%s:%u: '%s' component doesn't exists", file, line, comp_name);
  if (!hashtable_has(archetype->component_id, comp_name)) ERROR("%s:%u: Entity doesn't have '%s' component", file, line, comp_name);
#endif
  ComponentID cid = hashtable_get(archetype->component_id, comp_name);
#if DEVMODE
  if (cid == COMP_NOID) ERROR("%s:%u: Can't setup component '%s', it's an empty component", file, line, comp_name);
#endif
  usize offset = 0;
  for (usize i = 0; i < cid; i++) {
    offset += archetype->component_sizes[i];
  }
  return archetype->entity_creation_queue + (list_size(archetype->entity_creation_queue) - 1) * archetype->entity_size + offset;
}

void
__ecs_entity_creation_end(const char *file, u32 line) {
#if DEVMODE
  if (!world.on_entity_creation) ERROR("%s:%u: Trying to end an entity creation without one existing.", file, line);
#endif
  world.on_entity_creation = false;
  world.archetype_creation = 0;
}

static void
ecs_archetype_entity_remove_component(Archetype *archetype, Entity e, const char *comp_name, const char *file, u32 line, const char *fn_name) {
#if DEVMODE
  if (!world.on_system) ERROR("%s:%u: Function '%s' must be called inside of a system.", file, line, fn_name);
  if (!hashtable_has(world.components, comp_name)) ERROR("%s:%u: '%s' component doesn't exists", file, line, comp_name);
  if (e >= archetype->entities_amount) ERROR("%s:%u: Trying to remove component '%s' of unexisting entity.", file, line, comp_name);
  if (!hashtable_has(archetype->component_id, comp_name)) ERROR("%s:%u: Trying to remove component '%s', but the entity doesn't have it.", file, line, comp_name);
#endif
  archetype->entity_requested_remove_component_amount++;
  list_push(archetype->entity_remove_component[e], comp_name);
}

static void *
ecs_archetype_entity_insert_component(Archetype *archetype, Entity e, const char *comp_name, const char *file, u32 line, const char *fn_name0, const char *fn_name1) {
#if DEVMODE
  if (!world.on_system) ERROR("%s:%u: Function '%s' must be called inside of a system.", file, line, fn_name0);
  if (!hashtable_has(world.components, comp_name)) ERROR("%s:%u: '%s' component doesn't exists", file, line, comp_name);
  if (e >= archetype->entities_amount) ERROR("%s:%u: Trying to insert component '%s' to an unexisting entity.", file, line, comp_name);
  if (hashtable_has(archetype->component_id, comp_name)) ERROR("%s:%u: Trying to insert component '%s', but the entity already have it.", file, line, comp_name);
#endif
  archetype->entity_requested_insert_component_amount++;
  usize comp_size = hashtable_get(world.components, comp_name).size;
  if (comp_size == 0) ERROR("%s:%u: '%s' is an empty component. Use '%s' instead", file, line, comp_name, fn_name1);
  void *data = malloc(comp_size);
  list_push(archetype->entity_insert_component[e], comp_name);
  list_push(archetype->entity_insert_component_data[e], data);
  return data;
}

static void
ecs_archetype_entity_insert_empty_component(Archetype *archetype, Entity e, const char *comp_name, const char *file, u32 line, const char *fn_name0, const char *fn_name1) {
#if DEVMODE
  if (!world.on_system) ERROR("%s:%u: Function '%s' must be called inside of a system.", file, line, fn_name0);
  if (!hashtable_has(world.components, comp_name)) ERROR("%s:%u: '%s' component doesn't exists", file, line, comp_name);
  if (e >= archetype->entities_amount) ERROR("%s:%u: Trying to insert component '%s' to an unexisting entity.", file, line, comp_name);
  if (hashtable_has(archetype->component_id, comp_name)) ERROR("%s:%u: Trying to insert component '%s', but the entity already have it.", file, line, comp_name);
#endif
  archetype->entity_requested_insert_component_amount++;
  usize comp_size = hashtable_get(world.components, comp_name).size;
  if (comp_size != 0) ERROR("%s:%u: '%s' is not an empty component. Use '%s' instead", file, line, comp_name, fn_name1);
  list_push(archetype->entity_insert_component[e], comp_name);
  list_push(archetype->entity_insert_component_data[e], 0);
}

static bool
ecs_archetype_entity_has_component(Archetype *archetype, Entity e, const char *comp_name, const char *file, u32 line, const char *fn_name) {
#if DEVMODE
  if (!world.on_system) ERROR("%s:%u: Function '%s' must be called inside of a system.", file, line, fn_name);
  if (!hashtable_has(world.components, comp_name)) ERROR("%s:%u: '%s' component doesn't exists", file, line, comp_name);
  if (e >= archetype->entities_amount) ERROR("%s:%u: Trying to check component '%s' of an unexisting entity.", file, line, comp_name);
#endif
  return hashtable_has(archetype->component_id, comp_name);
}

static bool
ecs_archetype_entity_is_last_frame(Archetype *archetype, Entity e, const char *file, u32 line, const char *fn_name) {
#if DEVMODE
  if (!world.on_system) ERROR("%s:%u: Function '%s' must be called inside of a system.", file, line, fn_name);
  if (e >= archetype->entities_amount) ERROR("%s:%u: Trying to check if is entity last frame of an unexisting entity.", file, line);
#endif
  return archetype->entity_is_last_frame[e];
}

static bool
ecs_archetype_entity_is_first_frame(Archetype *archetype, Entity e, const char *file, u32 line, const char *fn_name) {
#if DEVMODE
  if (!world.on_system) ERROR("%s:%u: Function '%s' must be called inside of a system.", file, line, fn_name);
  if (e >= archetype->entities_amount) ERROR("%s:%u: Trying to check if is entity first frame of an unexisting entity.", file, line);
#endif
  return archetype->entity_is_first_frame[e];
}

static void
ecs_archetype_entity_destroy(Archetype *archetype, Entity e, const char *file, u32 line, const char *fn_name) {
#if DEVMODE
  if (!world.on_system) ERROR("%s:%u: Function '%s' must be called inside of a system.", file, line, fn_name);
  if (e >= archetype->entities_amount) ERROR("%s:%u: Trying to destroy unexisting entity.", file, line);
#endif
  archetype->entity_requested_destroy = true;
  archetype->entity_is_last_frame[e] = true;
}

void
__ecs_entity_remove_component(Entity e, const char *comp_name, const char *file, u32 line) {
  ecs_archetype_entity_remove_component(world.archetype_cur, e, comp_name, file, line, "ecs_entity_remove_component");
}

void *
__ecs_entity_insert_component(Entity e, const char *comp_name, const char *file, u32 line) {
  return ecs_archetype_entity_insert_component(world.archetype_cur, e, comp_name, file, line, "ecs_entity_insert_component", "ecs_entity_insert_empty_component");
}

void
__ecs_entity_insert_empty_component(Entity e, const char *comp_name, const char *file, u32 line) {
  ecs_archetype_entity_insert_empty_component(world.archetype_cur, e, comp_name, file, line, "ecs_entity_insert_empty_component", "ecs_entity_insert_component");
}

bool
__ecs_entity_has_component(Entity e, const char *comp_name, const char *file, u32 line) {
  return ecs_archetype_entity_has_component(world.archetype_cur, e, comp_name, file, line, "ecs_entity_has_component");
}

bool
__ecs_entity_is_last_frame(Entity e, const char *file, u32 line) {
  return ecs_archetype_entity_is_last_frame(world.archetype_cur, e, file, line, "ecs_entity_is_last_frame");
}

bool
__ecs_entity_is_first_frame(Entity e, const char *file, u32 line) {
  return ecs_archetype_entity_is_first_frame(world.archetype_cur, e, file, line, "ecs_entity_is_first_frame");
}

void
__ecs_entity_destroy(Entity e, const char *file, u32 line) {
  ecs_archetype_entity_destroy(world.archetype_cur, e, file, line, "ecs_entity_destroy");
}

void
__ecs_entity_get_reference(EntityReference *reference, Entity e, const char *file, u32 line) {
#if DEVMODE
  if (!world.on_system) ERROR("%s:%u: Function 'ecs_entity_get_reference' must be called inside of a system.", file, line);
  if (e >= world.archetype_cur->entities_amount) ERROR("%s:%u: Trying to get reference to an unexisting entity.", file, line);
  if (!reference) ERROR("%s:%u: Expected pointer to an entity reference, but got NULL", file, line);
  if ((*reference) != 0) ERROR("%s:%u: entity reference is already referecing an entity, please use 'ecs_entity_clean_reference' before calling this function", file, line);
#endif
  EntityReferenceInternal *ref = (EntityReferenceInternal *)reference;
  ref->archetype = world.archetype_cur->id + 1;
  ref->entity = e + 1;
  list_push(world.archetype_cur->entity_references[e], ref);
}

static EntityReferenceInternal
ecs_entity_reference_internal(EntityReference reference, const char *file, u32 line) {
#if DEVMODE
  if (!reference) ERROR("%s:%u: entity reference is NULL", file, line);
#endif
  EntityReferenceInternal ref = { .reference = reference };
  ref.archetype -= 1;
  ref.entity -= 1;
#if DEVMODE
  if (ref.archetype >= list_size(world.archetypes) || ref.entity >= world.archetypes[ref.archetype].entities_amount) ERROR("%s:%u: Invalid entity reference", file, line);
#endif
  return ref;
}

void
__ecs_entity_clean_reference(EntityReference *reference, const char *file, u32 line) {
#if DEVMODE
  if (!world.on_system) ERROR("%s:%u: Function 'ecs_entity_get_reference' must be called inside of a system.", file, line);
  if (!reference) ERROR("%s:%u: Expected pointer to an entity reference, but got NULL", file, line);
  if ((*reference) == 0) ERROR("%s:%u: Entity reference is already not referecing anything", file, line);
#endif
  EntityReferenceInternal ref = ecs_entity_reference_internal(*reference, file, line);
#if DEVMODE
  bool finded_ref_id = false;
#endif
  for (u32 i = 0; i < list_size(world.archetypes[ref.archetype].entity_references[ref.entity]); i++) {
    if (world.archetypes[ref.archetype].entity_references[ref.entity][i] != (EntityReferenceInternal *)reference) continue;
    list_remove(world.archetypes[ref.archetype].entity_references[ref.entity], i);
#if DEVMODE
    finded_ref_id = true;
#endif
    break;
  }
#if DEVMODE
  if (!finded_ref_id) ERROR("%s:%u: Pointer to entity reference is invalid, maybe realloc change it's location or this is a reference of another pointer", file, line);
#endif
  *reference = 0;
}

void *
__ecs_entity_reference_get_component(EntityReference reference, const char *comp_name, const char *file, u32 line) {
  EntityReferenceInternal ref = ecs_entity_reference_internal(reference, file, line);
#if DEVMODE
  if (!world.on_system) ERROR("%s:%u: Function 'ecs_entity_reference_get_component' must be called inside of a system.", file, line);
  if (!hashtable_has(world.components, comp_name)) ERROR("%s:%u: '%s' component doesn't exists", file, line, comp_name);
  if (!hashtable_has(world.archetypes[ref.archetype].component_id, comp_name)) ERROR("%s:%u: Entity reference doesn't have the component '%s'", file, line, comp_name);
#endif
  ComponentID cid = hashtable_get(world.archetypes[ref.archetype].component_id, comp_name);
#if DEVMODE
  if (cid == COMP_NOID) ERROR("%s:%u: Trying to get an empty component", file, line);
#endif
  return world.archetypes[ref.archetype].component_buffs[cid] + world.archetypes[ref.archetype].component_sizes[cid] * ref.entity;
}

void
__ecs_entity_reference_remove_component(EntityReference reference, const char *comp_name, const char *file, u32 line) {
  EntityReferenceInternal ref = ecs_entity_reference_internal(reference, file, line);
  ecs_archetype_entity_remove_component(&world.archetypes[ref.archetype], ref.entity, comp_name, file, line, "ecs_entity_reference_remove_component");
}

void *
__ecs_entity_reference_insert_component(EntityReference reference, const char *comp_name, const char *file, u32 line) {
  EntityReferenceInternal ref = ecs_entity_reference_internal(reference, file, line);
  return ecs_archetype_entity_insert_component(&world.archetypes[ref.archetype], ref.entity, comp_name, file, line, "ecs_entity_reference_insert_component", "ecs_entity_reference_insert_empty_component");
}

void
__ecs_entity_reference_insert_empty_component(EntityReference reference, const char *comp_name, const char *file, u32 line) {
  EntityReferenceInternal ref = ecs_entity_reference_internal(reference, file, line);
  ecs_archetype_entity_insert_empty_component(&world.archetypes[ref.archetype], ref.entity, comp_name, file, line, "ecs_entity_reference_insert_empty_component", "ecs_entity_reference_insert_component");
}

bool
__ecs_entity_reference_has_component(EntityReference reference, const char *comp_name, const char *file, u32 line) {
  EntityReferenceInternal ref = ecs_entity_reference_internal(reference, file, line);
  return ecs_archetype_entity_has_component(&world.archetypes[ref.archetype], ref.entity, comp_name, file, line, "ecs_entity_reference_has_component");
}

bool
__ecs_entity_reference_is_last_frame(EntityReference reference, const char *file, u32 line) {
  EntityReferenceInternal ref = ecs_entity_reference_internal(reference, file, line);
  return ecs_archetype_entity_is_last_frame(&world.archetypes[ref.archetype], ref.entity, file, line, "ecs_entity_reference_is_last_frame");
}

bool
__ecs_entity_reference_is_first_frame(EntityReference reference, const char *file, u32 line) {
  EntityReferenceInternal ref = ecs_entity_reference_internal(reference, file, line);
  return ecs_archetype_entity_is_first_frame(&world.archetypes[ref.archetype], ref.entity, file, line, "_ecs_entity_reference_is_first_frame");
}

void
__ecs_entity_reference_destroy(EntityReference reference, const char *file, u32 line) {
  EntityReferenceInternal ref = ecs_entity_reference_internal(reference, file, line);
  ecs_archetype_entity_destroy(&world.archetypes[ref.archetype], ref.entity, file, line, "ecs_entity_reference_destroy");
}

usize
ecs_entities_amount(void) {
  return world.archetype_cur->entities_amount;
}

void
ecs_entities_terminate(void) {
  for (ArchetypeID a = 0; a < list_size(world.archetypes); a++) {
    if (!world.archetypes[a].entities_amount) continue;
    for (Entity e = 0; e < world.archetypes[a].entities_amount; e++) {
      usize size = list_size(world.archetypes[a].entity_insert_component_data[e]);
      for (u32 i = 0; i < size; i++) {
        void *data = world.archetypes[a].entity_insert_component_data[e][i];
        if (data) free(data);
      }
      for (u32 i = 0; i < list_size(world.archetypes[a].entity_references[e]); i++) {
        world.archetypes[a].entity_references[e][i]->reference = 0;
      }
      list_destroy(world.archetypes[a].entity_insert_component_data[e]);
      list_destroy(world.archetypes[a].entity_insert_component[e]);
      list_destroy(world.archetypes[a].entity_remove_component[e]);
      list_destroy(world.archetypes[a].entity_references[e]);
    }
    usize siz = list_size(world.archetypes[a].component_buffs);
    for (ComponentID c = 0; c < siz; c++) {
      list_clear(world.archetypes[a].component_buffs[c]);
    }
    list_clear(world.archetypes[a].entity_references);
    list_clear(world.archetypes[a].entity_insert_component_data);
    list_clear(world.archetypes[a].entity_insert_component);
    list_clear(world.archetypes[a].entity_remove_component);
    list_clear(world.archetypes[a].entity_creation_queue);
    list_clear(world.archetypes[a].entity_is_last_frame);
    list_clear(world.archetypes[a].entity_is_first_frame);
    world.archetypes[a].entity_requested_insert_component_amount = 0;
    world.archetypes[a].entity_requested_insert_component_amount = 0;
    world.archetypes[a].entity_requested_create_amount = 0;
    world.archetypes[a].entity_requested_destroy = false;
    world.archetypes[a].entities_amount = 0;
  }
  world.entities_amount = 0;
}

void *
__ecs_get_component_list(const char *comp_name, const char *file, u32 line) {
#if DEVMODE
  if (!world.on_system) ERROR("%s:%u: Function 'ecs_get_component_list' must be called inside of a system.", file, line);
  if (!hashtable_has(world.components, comp_name)) ERROR("%s:%u: '%s' component doesn't exists", file, line, comp_name);
  if (!hashtable_has(world.archetype_cur->component_id, comp_name)) ERROR("%s:%u: Component '%s' is not required by system. Next batch of entities does not have it.", file, line, comp_name);
#endif
  ComponentID cid = hashtable_get(world.archetype_cur->component_id, comp_name);
#if DEVMODE
  if (cid == COMP_NOID) ERROR("%s:%u: Trying to get the component list of an empty component", file, line);
#endif
  return world.archetype_cur->component_buffs[cid];
}

void
__ecs_system_create(const char *name, SystemFn fn, SystemEvent event, const char *file, u32 line) {
#if DEVMODE
  if (hashtable_has(world.system_ids, name)) ERROR("%s:%u: System '%s' already exists", file, line, name);
#endif
  SystemID id = {
    .index = list_size(world.systems[event]),
    .event = event
  };
  list_grow(world.systems[event]);
  System *system = &world.systems[event][id.index];
  system->fn = fn;
  system->must_have = list_create(sizeof (const char *));
  system->must_not_have = list_create(sizeof (const char *));
#if DEVMODE
  system->creation_file = file;
  system->creation_line = line;
#endif
  system->active = false;
  system->paused = false;
  hashtable_insert(world.system_ids, name, id);
}

bool
__ecs_system_exists(const char *name) {
  return hashtable_has(world.system_ids, name);
}

void
__ecs_system_must_have(const char *name, usize comps_amount, const char *comps_names[comps_amount], const char *file, u32 line) {
#if DEVMODE
  if (!hashtable_has(world.system_ids, name)) ERROR("%s:%u: '%s' is not a system", file, line, name);
#endif
  SystemID id = hashtable_get(world.system_ids, name);
  System *system = &world.systems[id.event][id.index];
#if DEVMODE
  for (usize i = 0; i < comps_amount; i++) {
    if (!hashtable_has(world.components, comps_names[i])) ERROR("%s:%u: '%s' component doesn't exists", file, line, comps_names[i]);
    for (usize j = 0; j < list_size(system->must_not_have); j++) {
      if (strcmp(system->must_not_have[j], comps_names[i]) != 0) continue;
      ERROR("%s:%u: Entity must not have the component '%s'. No entity will be effected by the system", file, line, comps_names[i]);
    }
  }
#endif
  for (usize i = 0; i < comps_amount; i++) {
    bool skip = false;
    for (usize j = 0; j < list_size(system->must_have); j++) {
      if (strcmp(system->must_have[j], comps_names[i]) != 0) continue;
      skip = true;
      break;
    }
    if (skip) continue;
    list_push(system->must_have, comps_names[i]);
  }
}

void
__ecs_system_must_not_have(const char *name, usize comps_amount, const char *comps_names[comps_amount], const char *file, u32 line) {
#if DEVMODE
  if (!hashtable_has(world.system_ids, name)) ERROR("%s:%u: '%s' is not a system", file, line, name);
#endif
  SystemID id = hashtable_get(world.system_ids, name);
  System *system = &world.systems[id.event][id.index];
#if DEVMODE
  for (u32 i = 0; i < comps_amount; i++) {
    if (!hashtable_has(world.components, comps_names[i])) ERROR("%s:%u: '%s' component doesn't exists", file, line, comps_names[i]);
    for (usize j = 0; j < list_size(system->must_have); j++) {
      if (strcmp(system->must_have[j], comps_names[i]) != 0) continue;
      ERROR("%s:%u: Entity must have the component '%s'. No entity will be effected by the system", file, line, comps_names[i]);
    }
  }
#endif
  for (usize i = 0; i < comps_amount; i++) {
    bool skip = false;
    for (usize j = 0; j < list_size(system->must_not_have); j++) {
      if (strcmp(system->must_not_have[j], comps_names[i]) != 0) continue;
      skip = true;
      break;
    }
    if (skip) continue;
    list_push(system->must_not_have, comps_names[i]);
  }
}

void
__ecs_system_activate(const char *name, const char *file, u32 line) {
#if DEVMODE
  if (!hashtable_has(world.system_ids, name)) ERROR("%s:%u: '%s' is not a system", file, line, name);
#endif
  SystemID id = hashtable_get(world.system_ids, name);
  System *system = &world.systems[id.event][id.index];
  system->active = true;
}

void
__ecs_system_deactivate(const char *name, const char *file, u32 line) {
#if DEVMODE
  if (!hashtable_has(world.system_ids, name)) ERROR("%s:%u: '%s' is not a system", file, line, name);
#endif
  SystemID id = hashtable_get(world.system_ids, name);
  System *system = &world.systems[id.event][id.index];
  system->active = false;
}

void
ecs_system_deactivate_all(void) {
  for (SystemEvent event = 0; event < SYSTEM_EVENTS_AMOUNT; event++) {
    for (usize system_id = 0; system_id < list_size(world.systems[event]); system_id++) {
      world.systems[event][system_id].active = false;
      world.systems[event][system_id].paused = false;
    }
  }
}


void
__ecs_system_pause(const char *name, const char *file, u32 line) {
#if DEVMODE
  if (!hashtable_has(world.system_ids, name)) ERROR("%s:%u: '%s' is not a system", file, line, name);
#endif
  SystemID id = hashtable_get(world.system_ids, name);
  System *system = &world.systems[id.event][id.index];
  system->paused = true;
}

void
__ecs_system_unpause(const char *name, const char *file, u32 line) {
#if DEVMODE
  if (!hashtable_has(world.system_ids, name)) ERROR("%s:%u: '%s' is not a system", file, line, name);
#endif
  SystemID id = hashtable_get(world.system_ids, name);
  System *system = &world.systems[id.event][id.index];
  system->paused = false;
}

void
ecs_system_pause_event(SystemEvent event) {
  for (usize system_id = 0; system_id < list_size(world.systems[event]); system_id++) {
    world.systems[event][system_id].paused = true;
  }
}

void
ecs_system_unpause_event(SystemEvent event) {
  for (usize system_id = 0; system_id < list_size(world.systems[event]); system_id++) {
    world.systems[event][system_id].paused = false;
  }
}

static void
ecs_run_event_systems(SystemEvent event) {
  for (usize system_id = 0; system_id < list_size(world.systems[event]); system_id++) {
    System *system = &world.systems[event][system_id];
#if DEVMODE
    if (!list_size(system->must_have)) {
      ERROR("%s:%u: System must have a component filter. Forgot 'ecs_system_must_have'?", system->creation_file, system->creation_line);
    }
#endif
    if (!system->active || system->paused) continue;
    /* get all qualified archetypes */
    list_clear(world.archetype_queue);
    Component *comp = hashtable_get_address(world.components, system->must_have[0]);
    for (usize i = 0; i < list_size(comp->archetypes); i++) {
      /* must have components */
      Archetype *archetype = &world.archetypes[comp->archetypes[i]];
      for (usize j = 1; j < list_size(system->must_have); j++) {
        if (hashtable_has(archetype->component_id, system->must_have[j])) continue;
        archetype = 0;
        break;
      }
      if (!archetype) continue;
      /* must not have components */
      for (usize j = 0; j < list_size(system->must_not_have); j++) {
        if (!hashtable_has(archetype->component_id, system->must_not_have[j])) continue;
        archetype = 0;
        break;
      }
      if (archetype) list_push(world.archetype_queue, archetype);
    }
    for (usize i = 0; i < list_size(world.archetype_queue); i++) {
      world.archetype_cur = world.archetype_queue[i];
      if ((event == ON_CREATE && world.archetype_cur->entity_requested_create_amount == 0) || (event == ON_DESTROY && !world.archetype_cur->entity_requested_destroy)) continue;
      world.on_system = true;
      system->fn(world.archetype_cur->entities_amount);
      world.on_system = false;
    }
    world.archetype_cur = 0;
  }
}

static void
ecs_remove_component_from_entities(void) {
  for (ArchetypeID i = 0; i < list_size(world.archetypes); i++) {
    if (!world.archetypes[i].entity_requested_remove_component_amount) continue;
    for (SignedEntity e = world.archetypes[i].entities_amount - 1; e >= 0; e--) {
      if (list_size(world.archetypes[i].entity_remove_component[e]) == 0 || world.archetypes[i].entity_is_last_frame[e]) continue;
      list_clear(world.temp_comps_names);
      for (usize j = 0; j < list_size(world.archetypes[i].component_names); j++) {
        bool skip = false;
        for (usize k = 0; k < list_size(world.archetypes[i].entity_remove_component[e]); k++) {
          if (strcmp(world.archetypes[i].component_names[j], world.archetypes[i].entity_remove_component[e][k]) == 0) {
            skip = true;
            break;
          }
        }
        if (skip) continue;
        list_push(world.temp_comps_names, world.archetypes[i].component_names[j]);
      }
      Archetype *new_archetype = ecs_find_archetype(list_size(world.temp_comps_names), world.temp_comps_names, __FILE__, __LINE__);
      for (usize j = 0; j < list_size(new_archetype->component_names); j++) {
        ComponentID old = hashtable_get(world.archetypes[i].component_id, new_archetype->component_names[j]);
        if (old == COMP_NOID) continue;
        ComponentID new = hashtable_get(new_archetype->component_id, new_archetype->component_names[j]);
        usize size = new_archetype->component_sizes[new];
        list_grow(new_archetype->component_buffs[new]);
        memcpy(new_archetype->component_buffs[new] + size * (list_size(new_archetype->component_buffs[new]) - 1), world.archetypes[i].component_buffs[old] + size * e, size);
        list_remove(world.archetypes[i].component_buffs[old], e);
      }
      for (usize j = 0; j < list_size(world.archetypes[i].entity_remove_component[e]); j++) {
        ComponentID removed_component = hashtable_get(world.archetypes[i].component_id, world.archetypes[i].entity_remove_component[e][j]);
        if (removed_component == COMP_NOID) continue;
        list_remove(world.archetypes[i].component_buffs[removed_component], e);
      }
      if (list_size(world.archetypes[i].entity_insert_component[e]) > 0) {
        world.archetypes[i].entity_requested_insert_component_amount--;
        new_archetype->entity_requested_insert_component_amount++;
      }
      if (world.archetypes[i].entity_is_first_frame[e]) {
        world.archetypes[i].entity_requested_create_amount--;
        new_archetype->entity_requested_create_amount++;
      }
      for (u32 j = 0; j < list_size(world.archetypes[i].entity_references[e]); j++) {
        world.archetypes[i].entity_references[e][j]->archetype = new_archetype->id + 1;
        world.archetypes[i].entity_references[e][j]->entity = new_archetype->entities_amount + 1;
      }
      list_push(new_archetype->entity_references, world.archetypes[i].entity_references[e]);
      list_clear(world.archetypes[i].entity_remove_component[e]);
      list_push(new_archetype->entity_is_last_frame, false);
      list_push(new_archetype->entity_is_first_frame, new_archetype->entity_is_first_frame[e]);
      list_push(new_archetype->entity_insert_component_data, world.archetypes[i].entity_insert_component_data[e]);
      list_push(new_archetype->entity_insert_component, world.archetypes[i].entity_insert_component[e]);
      list_push(new_archetype->entity_remove_component, world.archetypes[i].entity_remove_component[e]);
      list_remove(world.archetypes[i].entity_is_last_frame, e);
      list_remove(world.archetypes[i].entity_is_first_frame, e);
      list_remove(world.archetypes[i].entity_references, e);
      list_remove(world.archetypes[i].entity_insert_component_data, e);
      list_remove(world.archetypes[i].entity_insert_component, e);
      list_remove(world.archetypes[i].entity_remove_component, e);
      world.archetypes[i].entities_amount--;
      new_archetype->entities_amount++;
    }
    world.archetypes[i].entity_requested_remove_component_amount = 0;
  }
}

static void
ecs_insert_component_into_entities(void) {
  for (ArchetypeID i = 0; i < list_size(world.archetypes); i++) {
    if (!world.archetypes[i].entity_requested_insert_component_amount) continue;
    for (SignedEntity e = world.archetypes[i].entities_amount - 1; e >= 0; e--) {
      if (list_size(world.archetypes[i].entity_insert_component[e]) == 0 || world.archetypes[i].entity_is_last_frame[e]) continue;
      list_clear(world.temp_comps_names);
      for (usize j = 0; j < list_size(world.archetypes[i].component_names); j++) {
        list_push(world.temp_comps_names, world.archetypes[i].component_names[j]);
      }
      for (usize j = 0; j < list_size(world.archetypes[i].entity_insert_component[e]); j++) {
        list_push(world.temp_comps_names, world.archetypes[i].entity_insert_component[e][j]);
      }
      Archetype *new_archetype = ecs_find_archetype(list_size(world.temp_comps_names), world.temp_comps_names, __FILE__, __LINE__);
      for (usize j = 0; j < list_size(world.archetypes[i].component_names); j++) {
        ComponentID old = hashtable_get(world.archetypes[i].component_id, world.archetypes[i].component_names[j]);
        if (old == COMP_NOID) continue;
        ComponentID new = hashtable_get(new_archetype->component_id, world.archetypes[i].component_names[j]);
        usize size = new_archetype->component_sizes[new];
        list_grow(new_archetype->component_buffs[new]);
        memcpy(new_archetype->component_buffs[new] + size * (list_size(new_archetype->component_buffs[new]) - 1), world.archetypes[i].component_buffs[old] + size * e, size);
        list_remove(world.archetypes[i].component_buffs[old], e);
      }
      for (usize j = 0; j < list_size(world.archetypes[i].entity_insert_component[e]); j++) {
        void *data = world.archetypes[i].entity_insert_component_data[e][j];
        if (!data) continue;
        ComponentID new = hashtable_get(new_archetype->component_id, world.archetypes[i].entity_insert_component[e][j]);
        usize size = new_archetype->component_sizes[new];
        list_grow(new_archetype->component_buffs[new]);
        memcpy(new_archetype->component_buffs[new] + size * (list_size(new_archetype->component_buffs[new]) - 1), data, size);
        free(data);
      }
      if (world.archetypes[i].entity_is_first_frame[e]) {
        world.archetypes[i].entity_requested_create_amount--;
        new_archetype->entity_requested_create_amount++;
      }
      for (u32 j = 0; j < list_size(world.archetypes[i].entity_references[e]); j++) {
        world.archetypes[i].entity_references[e][j]->archetype = new_archetype->id + 1;
        world.archetypes[i].entity_references[e][j]->entity = new_archetype->entities_amount + 1;
      }
      list_push(new_archetype->entity_references, world.archetypes[i].entity_references[e]);
      list_clear(world.archetypes[i].entity_insert_component_data[e]);
      list_clear(world.archetypes[i].entity_insert_component[e]);
      list_push(new_archetype->entity_is_last_frame, false);
      list_push(new_archetype->entity_is_first_frame, new_archetype->entity_is_first_frame[e]);
      list_push(new_archetype->entity_insert_component_data, world.archetypes[i].entity_insert_component_data[e]);
      list_push(new_archetype->entity_insert_component, world.archetypes[i].entity_insert_component[e]);
      list_push(new_archetype->entity_remove_component, world.archetypes[i].entity_remove_component[e]);
      list_remove(world.archetypes[i].entity_is_last_frame, e);
      list_remove(world.archetypes[i].entity_is_first_frame, e);
      list_remove(world.archetypes[i].entity_references, e);
      list_remove(world.archetypes[i].entity_insert_component_data, e);
      list_remove(world.archetypes[i].entity_insert_component, e);
      list_remove(world.archetypes[i].entity_remove_component, e);
      world.archetypes[i].entities_amount--;
      new_archetype->entities_amount++;
    }
    world.archetypes[i].entity_requested_insert_component_amount = 0;
  }
}

static void
ecs_destroy_entities(void) {
  for (ArchetypeID i = 0; i < list_size(world.archetypes); i++) {
    if (!world.archetypes[i].entity_requested_destroy) continue;
    for (SignedEntity e = world.archetypes[i].entities_amount - 1; e >= 0; e--) {
      if (!world.archetypes[i].entity_is_last_frame[e]) continue;
      for (Entity other = e; other < world.archetypes[i].entities_amount; other++) {
        for (u32 j = 0; j < list_size(world.archetypes[i].entity_references[other]); j++) {
          world.archetypes[i].entity_references[other][j]->entity--;
        }
      }
      for (ComponentID c = 0; c < world.archetypes[i].not_empty_component_amount; c++) {
        list_remove(world.archetypes[i].component_buffs[c], e);
      }
      for (usize j = 0; j < list_size(world.archetypes[i].entity_insert_component_data[e]); j++) {
        void *data = world.archetypes[i].entity_insert_component_data[e][j];
        if (data) free(data);
      }
      for (u32 j = 0; j < list_size(world.archetypes[i].entity_references[e]); j++) {
        world.archetypes[i].entity_references[e][j]->reference = 0;
      }
      list_destroy(world.archetypes[i].entity_insert_component_data[e]);
      list_destroy(world.archetypes[i].entity_insert_component[e]);
      list_destroy(world.archetypes[i].entity_remove_component[e]);
      list_destroy(world.archetypes[i].entity_references[e]);
      list_remove(world.archetypes[i].entity_is_last_frame, e);
      list_remove(world.archetypes[i].entity_is_first_frame, e);
      list_remove(world.archetypes[i].entity_references, e);
      list_remove(world.archetypes[i].entity_insert_component_data, e);
      list_remove(world.archetypes[i].entity_insert_component, e);
      list_remove(world.archetypes[i].entity_remove_component, e);
    }
    world.archetypes[i].entity_requested_destroy = false;
    world.archetypes[i].entities_amount--;
    world.entities_amount--;
  }
}

static void
ecs_create_entities(void) {
  for (ArchetypeID i = 0; i < list_size(world.archetypes); i++) {
    for (usize j = 0; j < list_size(world.archetypes[i].entity_creation_queue); j++) {
      void *base_entity = world.archetypes[i].entity_creation_queue + (j * world.archetypes[i].entity_size);
      for (ComponentID c = 0; c < world.archetypes[i].not_empty_component_amount; c++) {
        usize size = world.archetypes[i].component_sizes[c];
        void **component_buffs = world.archetypes[i].component_buffs;
        list_grow(component_buffs[c]);
        memcpy(component_buffs[c] + size * (list_size(component_buffs[c]) - 1), base_entity, size);
        base_entity += size;
      }
      list_push(world.archetypes[i].entity_is_last_frame, false);
      list_push(world.archetypes[i].entity_is_first_frame, true);
      list_push(world.archetypes[i].entity_remove_component, list_create(sizeof (const char *)));
      list_push(world.archetypes[i].entity_insert_component, list_create(sizeof (const char *)));
      list_push(world.archetypes[i].entity_insert_component_data, list_create(sizeof (void *)));
      world.archetypes[i].entity_requested_create_amount++;
      world.archetypes[i].entities_amount++;
      world.entities_amount++;
    }
    list_clear(world.archetypes[i].entity_creation_queue);
  }
}

static void
ecs_check_entities_first_frame(void) {
  for (ArchetypeID i = 0; i < list_size(world.archetypes); i++) {
    if (world.archetypes[i].entity_requested_create_amount == 0) continue;
    memset(world.archetypes[i].entity_is_first_frame, 0, list_size(world.archetypes[i].entity_is_first_frame) * sizeof (bool));
    world.archetypes[i].entity_requested_create_amount = 0;
  }
}

void
ecs_scene_start(void) {
  ecs_create_entities();
  ecs_run_event_systems(ON_SCENE_START);
}

void
ecs_scene_end(void) {
  ecs_run_event_systems(ON_SCENE_END);
}

void
ecs_update(void) {
  ecs_remove_component_from_entities();
  ecs_insert_component_into_entities();
  ecs_destroy_entities();
  ecs_create_entities();
  ecs_run_event_systems(ON_CREATE);
  ecs_run_event_systems(ON_PRE_UPDATE);
  ecs_run_event_systems(ON_UPDATE);
  ecs_run_event_systems(ON_POS_UPDATE);
  ecs_run_event_systems(ON_DESTROY);
  ecs_check_entities_first_frame();
}

void
ecs_draw_game(void) {
  ecs_run_event_systems(ON_PRE_DRAW_GAME);
  ecs_run_event_systems(ON_DRAW_GAME);
  ecs_run_event_systems(ON_POS_DRAW_GAME);
}

void
ecs_draw_ui(void) {
  ecs_run_event_systems(ON_PRE_DRAW_UI);
  ecs_run_event_systems(ON_DRAW_UI);
  ecs_run_event_systems(ON_POS_DRAW_UI);
}

void
ecs_draw_screen(void) {
  ecs_run_event_systems(ON_PRE_DRAW_SCREEN);
  ecs_run_event_systems(ON_DRAW_SCREEN);
  ecs_run_event_systems(ON_POS_DRAW_SCREEN);
}
