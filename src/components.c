#include "include/components.h"
#include "include/ecs.h"
#include "include/math.h"
#include "include/renderer.h"
#include "include/tilemap.h"

void
components_create(void) {
  ecs_component_create(V2f, "position");
  ecs_component_create(MovePosition, "move-position");
  ecs_component_create(Color, "color");
  ecs_component_create(TileType, "tile-type");
  ecs_component_create(EntityReference, "entity-reference");

  ecs_empty_component_create("input");
}
