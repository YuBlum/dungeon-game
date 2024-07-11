#include "include/components.h"
#include "include/ecs.h"
#include "include/global.h"
#include "include/renderer.h"

static const char *class_names[] = { "Fighter", "Thief", "Wizard" };

void
draw_save_slot_system(void) {
  CharName *char_name = ecs_get_component_list("char-name");
  Class *class = ecs_get_component_list("class");
  V2f *position = ecs_get_component_list("position");
  i32 *option_id = ecs_get_component_list("option-id");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    Color color = global.option_id == option_id[e] ? 0xffff00ff : 0xffffffff;
    if (char_name[e].size) {
      renderer_text(position[e], 1, true, true, color, 0, "%.*s, The %s", char_name[e].size, char_name[e].buff, class_names[class[e]]);
    } else {
      renderer_text(position[e], 1, true, true, color, 0, "New Game");
    }
  }
}
