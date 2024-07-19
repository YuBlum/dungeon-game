#include "engine/ecs.h"
#include "general/global.h"
#include "engine/types.h"

void
system_total_attribute_points(usize entities_amount) {
  u32 *u32_arg = ecs_get_component_list("u32-arg");
  for (Entity e = 0; e < entities_amount; e++) {
    u32_arg[e] = global.character_creation.total_attribute_points;
  }
}
