#include "game/components.h"
#include "engine/ecs.h"
#include "general/global.h"

void
system_submit_attribute_input(void) {
  i32 *attribute_points = ecs_get_component_list("attribute-points");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  Callback *callback = ecs_get_component_list("callback");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (global.menu.cursor_id == cursor_id[e] || global.menu.cursor_id_prv != cursor_id[e]) continue;
    callback[e](&attribute_points[e]);
  }
}
