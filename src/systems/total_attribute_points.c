#include "include/ecs.h"
#include "include/global.h"
#include "include/types.h"

void
total_attribute_points_system(void) {
  u32 *u32_arg = ecs_get_component_list("u32-arg");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    u32_arg[e] = global.total_attribute_points;
  }
}
