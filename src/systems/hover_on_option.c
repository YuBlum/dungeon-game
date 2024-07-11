#include "include/ecs.h"
#include "include/global.h"
#include "include/input.h"

void
hover_on_option_system(void) {
  i32 *cursor = ecs_get_component_list("cursor");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    global.option_id = (global.option_id + (input_key_pressed(KEY_DOWN) - input_key_pressed(KEY_UP))) % cursor[e];
    if (global.option_id < 0) {
      global.option_id = cursor[e] - 1;
    }
  }
}
