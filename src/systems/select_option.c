#include "include/components.h"
#include "include/ecs.h"
#include "include/global.h"
#include "include/input.h"

void
select_option_system(void) {
  u32 *id = ecs_get_component_list("option-id");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  Callback *callback = ecs_get_component_list("callback");
  CallbackArg *callback_arg = ecs_get_component_list("callback-arg");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (cursor_id[e] == global.menu.cursor_id && cursor_id[e] == global.menu.cursor_id_prv && global.menu.option_id[cursor_id[e]] == id[e] && input_key_pressed(KEY_A)) {
      callback[e](callback_arg[e]);
    }
  }
}
