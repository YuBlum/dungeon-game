#include "include/ecs.h"
#include "include/global.h"
#include "include/math.h"
#include "include/renderer.h"

void
draw_menu_hint_system(void) {
  V2f *position = ecs_get_component_list("position");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    renderer_text(position[e], 1, true, true, global.hint_color, 0, global.hint);
  }
}
