#include "engine/ecs.h"
#include "engine/math.h"
#include "engine/tilemap.h"

void
system_set_tile(void) {
  V2f *position = ecs_get_component_list("position");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    tilemap_set(position[e], e);
  }
}
