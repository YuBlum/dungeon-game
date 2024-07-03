#include "include/ecs.h"
#include "include/core.h"
#include "include/hashtable.h"
#include "include/types.h"
#include "include/list.h"

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
  bool *entity_alive;
  usize components_amount;
  ComponentID *components_ids;
  usize *component_sizes;
  void  **component_buffs;
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
    archetype->entity_alive = list_create(sizeof (bool));
    archetype->component_sizes = list_create(sizeof (usize));
    archetype->component_buffs = list_create(sizeof (void *));
    archetype->components_ids = hashtable_create(sizeof (ComponentID));
    archetype->components_amount = 0;
    archetype->entities_amount = 0;
  }
  return archetype;
}

void
__ecs_entity_create(Entity *out, usize comps_amount, const char *comps_names[comps_amount], const char *file, u32 line) {
  if (comps_amount == 0) {
    ERROR("%s:%u: Trying to create an entity without components", file, line);
  }
  Archetype *archetype = ecs_find_archetype(comps_amount, comps_names, file, line);
  for (u32 i = 0; i < comps_amount; i++) {
    Component *comp = hashtable_get_address(world.components, comps_names[i]);
    list_push(comp->archetypes, archetype->id);
    list_push(archetype->entity_alive, true);
    list_push(archetype->component_sizes, comp->size);
    list_push(archetype->component_buffs, list_create(comp->size));
    hashtable_insert(archetype->components_ids, comps_names[i], i);
    archetype->components_amount++;
  }
  EntityInternal *entity = (EntityInternal *)out;
  entity->archetype = archetype->id;
  entity->id = archetype->entities_amount;
  archetype->entities_amount++;
  world.entities_amount++;
  for (usize i = 0; i < archetype->components_amount; i++) {
    list_grow(archetype->component_buffs[i]);
  }
}

void *
__ecs_entity_get_component(Entity entity, const char *comp_name, const char *file, u32 line) {
  EntityInternal e;
  e.e = entity;
  if (e.archetype >= list_size(world.archetypes)) ERROR("%s:%u: Trying to get a component from a invalid entity", file, line);
  Archetype *archetype = &world.archetypes[e.archetype];
  if (e.id >= archetype->entities_amount) ERROR("%s:%u: Trying to get a component from a invalid entity", file, line);
  if (!hashtable_has(world.components, comp_name)) ERROR("%s:%u: '%s' component doesn't exists", file, line, comp_name);
  if (!hashtable_has(archetype->components_ids, comp_name)) return 0;
  ComponentID cid = hashtable_get(archetype->components_ids, comp_name);
  return archetype->component_buffs[cid] + archetype->component_sizes[cid] * e.id;
}

void
__ecs_entity_destroy(Entity entity, const char *file, u32 line) {
  EntityInternal e;
  e.e = entity;
  if (e.archetype >= list_size(world.archetypes)) ERROR("%s:%u: Trying to delete an invalid entity", file, line);
  Archetype *archetype = &world.archetypes[e.archetype];
  if (e.id >= archetype->entities_amount) ERROR("%s:%u: Trying to delete an invalid entity", file, line);
  if (!archetype->entity_alive[e.id]) ERROR("%s:%u: Trying to delete an invalid entity", file, line);
  archetype->entity_alive[e.id] = false;
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
