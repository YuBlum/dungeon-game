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
  ecs_component_create(bool, "input");
  ecs_component_create(TileType, "tile-type");
}
