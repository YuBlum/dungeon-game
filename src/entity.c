#include "include/types.h"
#include "include/list.h"

typedef struct {
  void  *components_data;
  usize *components_id;
} Archetype;

typedef struct {
  void **components;
  Archetype *archetypes;
} World;

static World world;

void
entity_system_create(void) {
  world.components = list_create(sizeof (void *));
  world.archetypes = list_create(sizeof (Archetype));
}

