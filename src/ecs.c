#include <string.h>
#include "include/ecs.h"
#include "include/core.h"
#include "include/hashtable.h"
#include "include/types.h"
#include "include/list.h"

typedef union {
  struct {
    u32 archetype;
    u32 id;
  };
  Entity e;
} EntityInternal;

typedef struct {
  u32 id;
  usize entities_amount;
  bool *entity_alive;
  usize components_amount;
  const char **components_names;
  usize *component_sizes;
  void  **component_buffs;
} Archetype;

typedef struct {
  u32 *archetypes;
  usize size;
} Component;

typedef struct EntityQuery {
  Archetype *archetypes;
} EntityQuery;

typedef struct {
  Component *components;
  Archetype *archetypes;
  System  *systems[SYSTEM_EVENTS_AMOUNT];
  EntityQuery *query;
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
  world.query = list_create(sizeof (EntityQuery));
}

void
__ecs_component_create(usize size, const char *name, const char *file, u32 line) {
  if (hashtable_has(world.components, name)) ERROR("%s:%u: '%s' component already exists", file, line, name);
  Component comp = { .archetypes = list_create(sizeof (u32)), .size = size };
  hashtable_insert(world.components, name, comp);
}

static Archetype *
ecs_component_find_archetype(u32 archetype_id, usize comp_current, usize comps_amount, const char *comps_names[comps_amount]) {
  if (comp_current >= comps_amount) return &world.archetypes[archetype_id];
  Component *comp = hashtable_get_address(world.components, comps_names[comp_current]);
  for (usize i = 0; i < list_size(comp->archetypes); i++) {
    if (archetype_id == comp->archetypes[i])
      return ecs_component_find_archetype(archetype_id, comp_current + 1, comps_amount, comps_names);
  }
  return 0;
}

EntityQuery *
ecs_query_entities(usize comps_amount, const char *comps_names[comps_amount]) {
  list_clear(world.query);
  Component *comp = hashtable_get_address(world.components, comps_names[0]);
  for (usize i = 0; i < list_size(comp->archetypes); i++) {
    Archetype *archetype = ecs_component_find_archetype(i, 1, comps_amount, comps_names);
    if (archetype) list_push(world.query, ((EntityQuery) { archetype }));
  }
  return world.query;
}

static Archetype *
ecs_archetype_with_components(usize comps_amount, const char *comps_names[comps_amount]) {
  Component *comp = hashtable_get_address(world.components, comps_names[0]);
  for (usize i = 0; i < list_size(comp->archetypes); i++) {
    if (world.archetypes[comp->archetypes[i]].components_amount != comps_amount) continue;
    Archetype *archetype = ecs_component_find_archetype(i, 1, comps_amount, comps_names);
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
    archetype->components_names = list_create(sizeof (char *));
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
    list_push(archetype->component_sizes, comp->size);
    list_push(archetype->component_buffs, list_create(comp->size));
    list_push(archetype->components_names, comps_names[i]);
    list_push(archetype->entity_alive, true);
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
  for (usize i = 0; i < list_size(archetype->components_names); i++) {
    if (strcmp(archetype->components_names[i], comp_name) == 0) {
      return archetype->component_buffs[i] + archetype->component_sizes[i] * e.id;
    }
  }
  return 0;
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

/*
void
__ecs_entity_add_component(Entity entity, const char *comp, const char *file, u32 line) {
}
*/

void
__ecs_system_create(System fn, SystemEvent event, const char *file, u32 line) {
  for (SystemEvent j = 0; j < SYSTEM_EVENTS_AMOUNT; j++) {
    for (usize i = 0; i < list_size(world.systems[event]); i++) {
      ERROR("%s:%u: System already exists on event %s", file, line, system_event_str[j]);
    }
  }
  list_push(world.systems[event], fn);
}

void
ecs_update(void) {
  for (SystemEvent event = SYS_PRE_UPDATE; event <= SYS_POS_UPDATE; event++) {
    for (usize system = 0; system < list_size(world.systems[event]); system++) {
      world.systems[event][system]();
    }
  }
}

void
ecs_draw(void) {
  for (SystemEvent event = SYS_PRE_DRAW; event <= SYS_POS_DRAW; event++) {
    for (usize system = 0; system < list_size(world.systems[event]); system++) {
      world.systems[event][system]();
    }
  }
}
