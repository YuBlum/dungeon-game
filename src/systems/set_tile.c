#include "include/ecs.h"
#include "include/math.h"
#include "include/tilemap.h"

void
set_tile_system(void) {
  V2f *position = ecs_get_component_list("position");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    tilemap_set(position[e], e);
  }
}
