#include "include/components.h"
#include "include/ecs.h"
#include "include/global.h"
#include "include/input.h"

void
cursor_navigation_system(void) {
  u32 *id = ecs_get_component_list("cursor-id");
  Cursor *cursor = ecs_get_component_list("cursor");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (global.cursor_id != id[e]) continue;
    if (global.option_id[id[e]] >= cursor[e].options_amount) global.option_id[id[e]] = 0;
    i32 move = cursor[e].horizontal ? (input_key_pressed(KEY_RIGHT) - input_key_pressed(KEY_LEFT)) : (input_key_pressed(KEY_DOWN) - input_key_pressed(KEY_UP));
    global.option_id_prv[id[e]] = global.option_id[id[e]];
    if (move < 0 && global.option_id[id[e]] == 0) {
      global.option_id[id[e]] = cursor[e].options_amount - 1;
    } else if (move > 0 && global.option_id[id[e]] == cursor[e].options_amount - 1) {
      global.option_id[id[e]] = 0;
    } else {
      global.option_id[id[e]] += move;
    }
  }
}
