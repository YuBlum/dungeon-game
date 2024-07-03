#include "include/ecs.h"
#include "include/core.h"
#include "include/hashtable.h"
#include "include/types.h"
#include "include/list.h"
#include <string.h>

typedef u32 ComponentID, ArchetypeID;

typedef struct {
  Entity e;
  const char *comp_name;
} EntityChangeComponent;

typedef struct {
  const char **component_names;
  ComponentID *component_id;
  void  **component_buffs;
  usize *component_sizes;
  usize component_amount;
  usize entities_amount;
  bool *entity_destroy;
  const char **entity_remove_component;
  const char **entity_insert_component;
  usize entity_remove_component_amount;
  usize entity_insert_component_amount;
  usize entity_destroy_amount;
  void *entity_creation_queue;
  usize entity_size;
  ArchetypeID id;
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
  bool on_entity_creation;
  bool on_system;
  const char **temp_comps_names;
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
  world.temp_comps_names = list_create(sizeof (const char *));
  world.archetype_cur = 0;
  world.on_entity_creation = false;
  world.on_system = false;
}

void
__ecs_component_create(usize size, const char *name, const char *file, u32 line) {
  if (hashtable_has(world.components, name)) ERROR("%s:%u: '%s' component already exists", file, line, name);
  Component comp = { .archetypes = list_create(sizeof (ArchetypeID)), .size = size };
  hashtable_insert(world.components, name, comp);
}

static Archetype *
ecs_find_archetype(usize comps_amount, const char *comps_names[comps_amount], const char *file, u32 line) {
  for (u32 i = 0; i < comps_amount; i++) {
    if (!hashtable_has(world.components, comps_names[i])) ERROR("%s:%u: '%s' component doesn't exists", file, line, comps_names[i]);
  }
  /* check for existing archetype */
  Archetype *archetype = 0;
  Component *comp = hashtable_get_address(world.components, comps_names[0]);
  for (usize i = 0; i < list_size(comp->archetypes); i++) {
    if (world.archetypes[comp->archetypes[i]].component_amount != comps_amount) continue;
    Archetype *archetype_test = &world.archetypes[comp->archetypes[i]];
    for (usize j = 1; j < comps_amount; j++) {
      if (!hashtable_has(archetype_test->component_id, comps_names[j])) {
        archetype = 0;
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
    archetype->entities_amount = 0;
    archetype->entity_size = 0;
    for (usize i = 0; i < comps_amount; i++) {
      Component *comp = hashtable_get_address(world.components, comps_names[i]);
      list_push(comp->archetypes, archetype->id);
      hashtable_insert(archetype->component_id, comps_names[i], i);
      list_push(archetype->component_names, comps_names[i]);
      list_push(archetype->component_sizes, comp->size);
      list_push(archetype->component_buffs, list_create(comp->size));
      archetype->component_amount++;
      archetype->entity_size += comp->size;
    }
    archetype->entity_creation_queue = list_create(archetype->entity_size);
    archetype->entity_destroy = list_create(sizeof (bool));
    archetype->entity_remove_component = list_create(sizeof (const char *));
    archetype->entity_insert_component = list_create(sizeof (const char *));
    archetype->entity_destroy_amount = 0;
    archetype->entity_remove_component_amount = 0;
    archetype->entity_insert_component_amount = 0;
  }
  return archetype;
}

void
__ecs_entity_creation_begin(usize comps_amount, const char *comps_names[comps_amount], const char *file, u32 line) {
  if (world.on_entity_creation) ERROR("%s:%u: Trying to start an entity creation with another already happening.", file, line);
  if (comps_amount == 0) ERROR("%s:%u: Trying to start an entity creation without components", file, line);
  world.on_entity_creation = true;
  Archetype *archetype = ecs_find_archetype(comps_amount, comps_names, file, line);
  world.archetype_cur = archetype;
  list_grow(archetype->entity_creation_queue);
}

void *
__ecs_entity_creation_setup_component(const char *comp_name, const char *file, u32 line) {
  if (!world.on_entity_creation) ERROR("%s:%u: Trying to setup a component outside of an entity creation.", file, line);
  Archetype *archetype = world.archetype_cur;
  if (!hashtable_has(world.components, comp_name)) ERROR("%s:%u: '%s' component doesn't exists", file, line, comp_name);
  if (!hashtable_has(archetype->component_id, comp_name)) ERROR("%s:%u: Entity doesn't have '%s' component", file, line, comp_name);
  ComponentID cid = hashtable_get(archetype->component_id, comp_name);
  usize offset = 0;
  for (usize i = 0; i < cid; i++) {
    offset += archetype->component_sizes[i];
  }
  return archetype->entity_creation_queue + (list_size(archetype->entity_creation_queue) - 1) * archetype->entity_size + offset;
}

void
__ecs_entity_creation_end(const char *file, u32 line) {
  if (!world.on_entity_creation) ERROR("%s:%u: Trying to end an entity creation without one existing.", file, line);
  world.on_entity_creation = false;
  world.archetype_cur = 0;
}

void
__ecs_entity_remove_component(Entity e, const char *comp_name, const char *file, u32 line) {
  if (!world.on_system) ERROR("%s:%u: Function 'ecs_entity_remove_component' must be called inside of a system.", file, line);
  if (e >= world.archetype_cur->entities_amount) ERROR("%s:%u: Trying to remove component '%s' of unexisting entity.", file, line, comp_name);
  if (!hashtable_has(world.archetype_cur->component_id, comp_name)) ERROR("%s:%u: Trying to remove component '%s', but the entity doesn't have it.", file, line, comp_name);
  world.archetype_cur->entity_remove_component[e] = comp_name;
  world.archetype_cur->entity_remove_component_amount++;
}

void
__ecs_entity_destroy(Entity e, const char *file, u32 line) {
  if (!world.on_system) ERROR("%s:%u: Function 'ecs_entity_destroy' must be called inside of a system.", file, line);
  if (e >= world.archetype_cur->entities_amount) ERROR("%s:%u: Trying to destroy unexisting entity.", file, line);
  world.archetype_cur->entity_destroy[e] = true;
  world.archetype_cur->entity_destroy_amount++;
}

usize
ecs_entities_amount(void) {
  return world.archetype_cur->entities_amount;
}

void *
__ecs_get_component_list(const char *comp_name, const char *file, u32 line) {
  if (!world.on_system) ERROR("%s:%u: Function 'ecs_get_component_list' must be called inside of a system.", file, line);
  if (!hashtable_has(world.components, comp_name)) ERROR("%s:%u: '%s' component doesn't exists", file, line, comp_name);
  if (!hashtable_has(world.archetype_cur->component_id, comp_name)) ERROR("%s:%u: Component '%s' is not required by system. Next batch of entities does not have it.", file, line, comp_name);
  ComponentID cid = hashtable_get(world.archetype_cur->component_id, comp_name);
  return world.archetype_cur->component_buffs[cid];
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
        if (!hashtable_has(archetype->component_id, system->comps[j])) {
          archetype = 0;
          break;
        }
      }
      if (archetype) list_push(world.archetype_queue, archetype);
    }
    for (usize i = 0; i < list_size(world.archetype_queue); i++) {
      world.archetype_cur = world.archetype_queue[i];
      world.on_system = true;
      system->fn();
      world.on_system = false;
    }
    world.archetype_cur = 0;
  }
}

void
ecs_update(void) {
  /* remove component from entities */
  for (ArchetypeID i = 0; i < list_size(world.archetypes); i++) {
    if (world.archetypes[i].entity_remove_component_amount == 0) continue;
    for (SignedEntity e = world.archetypes->entities_amount - 1; e >= 0; e--) {
      if (!world.archetypes[i].entity_remove_component[e] || world.archetypes[i].entity_destroy[e]) continue;
      list_clear(world.temp_comps_names);
      for (usize j = 0; j < list_size(world.archetypes[i].component_names); j++) {
        if (strcmp(world.archetypes[i].component_names[j], world.archetypes[i].entity_remove_component[e]) == 0) continue;
        list_push(world.temp_comps_names, world.archetypes[i].component_names[j]);
      }
      Archetype *new_archetype = ecs_find_archetype(list_size(world.temp_comps_names), world.temp_comps_names, __FILE__, __LINE__);
      for (usize j = 0; j < list_size(new_archetype->component_names); j++) {
        ComponentID old = hashtable_get(world.archetypes[i].component_id, new_archetype->component_names[j]);
        ComponentID new = hashtable_get(new_archetype->component_id, new_archetype->component_names[j]);
        usize size = new_archetype->component_sizes[new];
        list_grow(new_archetype->component_buffs[new]);
        memcpy(new_archetype->component_buffs[new] + size * (list_size(new_archetype->component_buffs[new]) - 1), world.archetypes[i].component_buffs[old] + size * e, size);
        list_remove(world.archetypes[i].component_buffs[old], e);
      }
      ComponentID removed_component = hashtable_get(world.archetypes[i].component_id, world.archetypes[i].entity_remove_component[e]);
      list_remove(world.archetypes[i].component_buffs[removed_component], e);
      if (world.archetypes[i].entity_insert_component[e]) {
        new_archetype->entity_insert_component++;
        world.archetypes[i].entity_insert_component_amount--;
      }
      list_push(new_archetype->entity_destroy, false);
      list_push(new_archetype->entity_remove_component, 0);
      list_push(new_archetype->entity_insert_component, world.archetypes[i].entity_insert_component[e]);
      list_remove(world.archetypes[i].entity_destroy, e);
      list_remove(world.archetypes[i].entity_remove_component, e);
      list_remove(world.archetypes[i].entity_insert_component, e);
      world.archetypes[i].entities_amount--;
      new_archetype->entities_amount++;
    }
    world.archetypes[i].entity_remove_component_amount = 0;
  }
  /* destroy entities */
  for (ArchetypeID i = 0; i < list_size(world.archetypes); i++) {
    if (world.archetypes[i].entity_destroy_amount == 0) continue;
    for (SignedEntity e = world.archetypes->entities_amount - 1; e >= 0; e--) {
      if (!world.archetypes[i].entity_destroy[e]) continue;
      for (ComponentID c = 0; c < world.archetypes[i].component_amount; c++) {
        list_remove(world.archetypes[i].component_buffs[c], e);
      }
      if (world.archetypes[i].entity_remove_component[e]) world.archetypes[i].entity_remove_component_amount--;
      if (world.archetypes[i].entity_insert_component[e]) world.archetypes[i].entity_insert_component_amount--;
      list_remove(world.archetypes[i].entity_destroy, e);
      list_remove(world.archetypes[i].entity_remove_component, e);
      list_remove(world.archetypes[i].entity_insert_component, e);
    }
    world.archetypes[i].entity_destroy_amount = 0;
    world.archetypes[i].entities_amount--;
    world.entities_amount--;
  }
  /* create queued entities */
  for (ArchetypeID i = 0; i < list_size(world.archetypes); i++) {
    if (list_size(world.archetypes[i].entity_creation_queue) == 0) continue;
    for (usize j = 0; j < list_size(world.archetypes[i].entity_creation_queue); j++) {
      void *base_entity = world.archetypes[i].entity_creation_queue + (j * world.archetypes[i].entity_size);
      for (ComponentID c = 0; c < world.archetypes[i].component_amount; c++) {
        usize size = world.archetypes[i].component_sizes[c];
        void **component_buffs = world.archetypes[i].component_buffs;
        list_grow(component_buffs[c]);
        memcpy(component_buffs[c] + size * (list_size(component_buffs[c]) - 1), base_entity, size);
        base_entity += size;
      }
      list_push(world.archetypes[i].entity_destroy, false);
      list_push(world.archetypes[i].entity_remove_component, 0);
      list_push(world.archetypes[i].entity_insert_component, 0);
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
