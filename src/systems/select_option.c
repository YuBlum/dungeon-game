#include "include/components.h"
#include "include/ecs.h"
#include "include/global.h"
#include "include/input.h"

void
select_option_system(void) {
  i32 *id = ecs_get_component_list("option-id");
  OptionCallback *callback = ecs_get_component_list("option-callback");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (global.option_id == id[e] && input_key_pressed(KEY_A)) {
      callback[e]();
    }
  }
}
