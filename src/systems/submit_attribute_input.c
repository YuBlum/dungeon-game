#include "include/components.h"
#include "include/ecs.h"
#include "include/global.h"

void
submit_attribute_input_system(void) {
  i32 *attribute_points = ecs_get_component_list("attribute-points");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  Callback *callback = ecs_get_component_list("callback");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (global.cursor_id == cursor_id[e] || global.cursor_id_prv != cursor_id[e]) continue;
    callback[e](&attribute_points[e]);
  }
}
