#include "engine/ecs.h"
#include "engine/math.h"
#include "engine/tilemap.h"
#include "engine/types.h"

void
system_set_tile(usize entities_amount) {
  V2f *position = ecs_get_component_list("position");
  for (Entity e = 0; e < entities_amount; e++) {
    tilemap_set(position[e], e);
  }
}
