#include "general/global.h"
#include "engine/ecs.h"
#include "engine/input.h"
#include "game/components.h"

void
system_cursor_navigation(void) {
  u32 *id = ecs_get_component_list("cursor-id");
  Cursor *cursor = ecs_get_component_list("cursor");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (global.menu.cursor_id != id[e]) continue;
    if (global.menu.option_id[id[e]] >= global.menu.option_amount[id[e]]) global.menu.option_id[id[e]] = 0;
    i32 move;
    Key backward, forward;
    if (cursor[e].horizontal) {
      forward  = KEY_RIGHT;
      backward = KEY_LEFT;
    } else {
      forward  = KEY_DOWN;
      backward = KEY_UP;
    }
    if (cursor[e].wrap) {
      move = input_key_pressed(forward) - input_key_pressed(backward);
    } else {
      move = (input_key_pressed(forward) || input_key_repeated(forward)) - (input_key_pressed(backward) || input_key_repeated(backward));
    }
    global.menu.option_id_prv[id[e]] = global.menu.option_id[id[e]];
    if (move < 0 && global.menu.option_id[id[e]] == 0) {
      if (cursor[e].wrap) global.menu.option_id[id[e]] = global.menu.option_amount[id[e]] - 1;
    } else if (move > 0 && global.menu.option_id[id[e]] == global.menu.option_amount[id[e]] - 1) {
      if (cursor[e].wrap) global.menu.option_id[id[e]] = 0;
    } else {
      global.menu.option_id[id[e]] += move;
    }
  }
}
