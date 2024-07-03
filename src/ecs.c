#include "include/ecs.h"
#include "include/core.h"
#include "include/hashtable.h"
#include "include/types.h"
#include "include/list.h"
#include <string.h>

typedef u32 ComponentID, ArchetypeID;

typedef union {
  struct {
    u32 archetype;
    u32 id;
  };
  Entity e;
} EntityInternal;

typedef struct {
  ArchetypeID id;
  usize entities_amount;
  usize components_amount;
  ComponentID *components_ids;
  usize *component_sizes;
  void  **component_buffs;
  void *entity_creation_queue;
  usize entity_size;
} Archetype;

typedef struct {
  ArchetypeID *archetypes;
  usize size;
} Component;

typedef struct {
  SystemFn fn;
  const char **comps;
} System;

typedef struct {
  Component *components;
  Archetype *archetypes;
  System  *systems[SYSTEM_EVENTS_AMOUNT];
  Archetype **archetype_queue;
  Archetype *archetype_cur;
  usize entities_amount;
  EntityInternal entity_cur;
  bool on_entity_creation;
} World;

static World world;

static const char *system_event_str[] = {
  "SYS_PRE_UPDATE",
  "SYS_UPDATE",
  "SYS_POS_UPDATE",
  "SYS_PRE_DRAW",
  "SYS_DRAW",
  "SYS_POS_DRAW",
};
_Static_assert(sizeof (system_event_str) / sizeof (char *) == SYSTEM_EVENTS_AMOUNT, "system_event_str doesn't handle all system events");

void
ecs_create(void) {
  world.components = hashtable_create(sizeof (Component));
  world.archetypes = list_create(sizeof (Archetype));
  for (SystemEvent event = 0; event < SYSTEM_EVENTS_AMOUNT; event++) {
    world.systems[event] = list_create(sizeof (System));
  }
  world.archetype_queue = list_create(sizeof (Archetype *));
  world.archetype_cur = 0;
  world.on_entity_creation = false;
}

void
__ecs_component_create(usize size, const char *name, const char *file, u32 line) {
  if (hashtable_has(world.components, name)) ERROR("%s:%u: '%s' component already exists", file, line, name);
  Component comp = { .archetypes = list_create(sizeof (ArchetypeID)), .size = size };
  hashtable_insert(world.components, name, comp);
}

static Archetype *
ecs_archetype_with_components(usize comps_amount, const char *comps_names[comps_amount]) {
  Component *comp = hashtable_get_address(world.components, comps_names[0]);
  for (usize i = 0; i < list_size(comp->archetypes); i++) {
    if (world.archetypes[comp->archetypes[i]].components_amount != comps_amount) continue;
    Archetype *archetype = &world.archetypes[comp->archetypes[i]];
    for (usize j = 1; j < comps_amount; j++) {
      if (!hashtable_has(archetype->components_ids, comps_names[j])) {
        archetype = 0;
        break;
      }
    }
    if (archetype) return archetype;
  }
  return 0;
}

static Archetype *
ecs_find_archetype(usize comps_amount, const char *comps_names[comps_amount], const char *file, u32 line) {
  /* check for existing archetype */
  for (u32 i = 0; i < comps_amount; i++) {
    if (!hashtable_has(world.components, comps_names[i])) ERROR("%s:%u: '%s' component doesn't exists", file, line, comps_names[i]);
  }
  Archetype *archetype = ecs_archetype_with_components(comps_amount, comps_names);
  /* create new archetype */
  if (!archetype) {
    u32 archetype_id = list_size(world.archetypes);
    list_grow(world.archetypes);
    archetype = &world.archetypes[archetype_id];
    archetype->id = archetype_id;
    archetype->component_sizes = list_create(sizeof (usize));
    archetype->component_buffs = list_create(sizeof (void *));
    archetype->components_ids = hashtable_create(sizeof (ComponentID));
    archetype->components_amount = 0;
    archetype->entities_amount = 0;
    archetype->entity_size = 0;
    for (usize i = 0; i < comps_amount; i++) {
      hashtable_insert(archetype->components_ids, comps_names[i], i);
      Component *comp = hashtable_get_address(world.components, comps_names[i]);
      list_push(comp->archetypes, archetype->id);
      list_push(archetype->component_sizes, comp->size);
      list_push(archetype->component_buffs, list_create(comp->size));
      archetype->components_amount++;
      archetype->entity_size += comp->size;
    }
    archetype->entity_creation_queue = list_create(archetype->entity_size);
  }
  return archetype;
}

void
__ecs_entity_creation_begin(usize comps_amount, const char *comps_names[comps_amount], const char *file, u32 line) {
  if (world.on_entity_creation) ERROR("%s:%u: Trying to start an entity creation with another already happening.", file, line);
  if (comps_amount == 0) ERROR("%s:%u: Trying to start an entity creation without components", file, line);
  world.on_entity_creation = true;
  Archetype *archetype = ecs_find_archetype(comps_amount, comps_names, file, line);
  world.entity_cur.archetype = archetype->id;
  world.entity_cur.id = list_size(archetype->entity_creation_queue);
  list_grow(archetype->entity_creation_queue);
}

void *
__ecs_entity_creation_setup_component(const char *comp_name, const char *file, u32 line) {
  if (!world.on_entity_creation) ERROR("%s:%u: Trying to setup a component outside of an entity creation.", file, line);
  Archetype *archetype = &world.archetypes[world.entity_cur.archetype];
  if (!hashtable_has(world.components, comp_name)) ERROR("%s:%u: '%s' component doesn't exists", file, line, comp_name);
  if (!hashtable_has(archetype->components_ids, comp_name)) ERROR("%s:%u: Entity doesn't have '%s' component", file, line, comp_name);
  ComponentID cid = hashtable_get(archetype->components_ids, comp_name);
  usize offset = 0;
  for (usize i = 0; i < cid; i++) {
    offset += archetype->component_sizes[i];
  }
  return archetype->entity_creation_queue + (world.entity_cur.id * archetype->entity_size) + offset;
}

void
__ecs_entity_creation_end(const char *file, u32 line) {
  if (!world.on_entity_creation) ERROR("%s:%u: Trying to end an entity creation without one existing.", file, line);
  world.on_entity_creation = false;
}

void *
__ecs_get_component_list(const char *comp_name, const char *file, u32 line) {
  if (!world.archetype_cur) ERROR("%s:%u: Function 'ecs_get_component_list' needs to be called inside of a system.", file, line);
  if (!hashtable_has(world.components, comp_name)) ERROR("%s:%u: '%s' component doesn't exists", file, line, comp_name);
  if (!hashtable_has(world.archetype_cur->components_ids, comp_name)) ERROR("%s:%u: Component '%s' is not required by system. Next batch of entities does not have it.", file, line, comp_name);
  ComponentID cid = hashtable_get(world.archetype_cur->components_ids, comp_name);
  return world.archetype_cur->component_buffs[cid];
}

usize
ecs_entities_amount(void) {
  return world.archetype_cur->entities_amount;
}

Entity
__ecs_get_entity_from_id(EntityID id, const char *file, u32 line) {
  if (!world.archetype_cur) ERROR("%s:%u: Function 'ecs_get_entity_from_id' needs to be called inside of a system.", file, line);
  EntityInternal entity;
  entity.archetype = world.archetype_cur->id;
  entity.id = id;
  if (entity.id >= world.archetype_cur->entities_amount) ERROR("%s:%u: Trying to get invalid entity (%u:%u)", file, line, entity.archetype, entity.id);
  return entity.e;
}

/*
void
__ecs_entity_add_component(Entity entity, const char *comp, const char *file, u32 line) {
}
*/

void
__ecs_system_create(SystemFn fn, SystemEvent event, usize comps_amount, const char *comps_names[comps_amount], const char *file, u32 line) {
  for (SystemEvent j = 0; j < SYSTEM_EVENTS_AMOUNT; j++) {
    for (usize i = 0; i < list_size(world.systems[event]); i++) {
      ERROR("%s:%u: System already exists on event %s", file, line, system_event_str[j]);
    }
  }
  for (u32 i = 0; i < comps_amount; i++) {
    if (!hashtable_has(world.components, comps_names[i])) ERROR("%s:%u: '%s' component doesn't exists", file, line, comps_names[i]);
  }
  System system = {
    .fn = fn,
    .comps = list_create(sizeof (const char *))
  };
  for (usize i = 0; i < comps_amount; i++) {
    list_push(system.comps, comps_names[i]);
  }
  list_push(world.systems[event], system);
}

static void
ecs_run_event_systems(SystemEvent event) {
  for (usize system_id = 0; system_id < list_size(world.systems[event]); system_id++) {
    System *system = &world.systems[event][system_id];
    /* get all archetypes that has the correct components */
    list_clear(world.archetype_queue);
    Component *comp = hashtable_get_address(world.components, system->comps[0]);
    for (usize i = 0; i < list_size(comp->archetypes); i++) {
      Archetype *archetype = &world.archetypes[comp->archetypes[i]];
      for (usize j = 1; j < list_size(system->comps); j++) {
        if (!hashtable_has(archetype->components_ids, system->comps[j])) {
          archetype = 0;
          break;
        }
      }
      if (archetype) list_push(world.archetype_queue, archetype);
    }
    for (usize i = 0; i < list_size(world.archetype_queue); i++) {
      world.archetype_cur = world.archetype_queue[i];
      system->fn();
    }
    world.archetype_cur = 0;
  }
}

void
ecs_update(void) {
  /* create entities queued for creation */
  for (ArchetypeID i = 0; i < list_size(world.archetypes); i++) {
    if (list_size(world.archetypes[i].entity_creation_queue) == 0) continue;
    for (usize j = 0; j < list_size(world.archetypes[i].entity_creation_queue); j++) {
      void *base_entity = world.archetypes[i].entity_creation_queue + (j * world.archetypes[i].entity_size);
      for (ComponentID k = 0; k < list_size(world.archetypes[i].component_buffs); k++) {
        usize size = world.archetypes[i].component_sizes[k];
        void **component_buffs = world.archetypes[i].component_buffs;
        list_grow(component_buffs[k]);
        memcpy(component_buffs[k] + size * (list_size(component_buffs[k]) - 1), base_entity, size);
        base_entity += size;
      }
      world.archetypes[i].entities_amount++;
      world.entities_amount++;
    }
    list_clear(world.archetypes[i].entity_creation_queue);
  }
  /* run on update event systems */
  for (SystemEvent event = SYS_PRE_UPDATE; event <= SYS_POS_UPDATE; event++) {
    ecs_run_event_systems(event);
  }
}

void
ecs_draw(void) {
  for (SystemEvent event = SYS_PRE_DRAW; event <= SYS_POS_DRAW; event++) {
    ecs_run_event_systems(event);
  }
}
