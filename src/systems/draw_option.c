#include "include/ecs.h"
#include "include/global.h"
#include "include/math.h"
#include "include/renderer.h"

void
draw_option_system(void) {
  V2f *position = ecs_get_component_list("position");
  const char **tag = ecs_get_component_list("tag");
  i32 *option_id = ecs_get_component_list("option-id");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    Color color = option_id[e] == global.option_id ? 0xffff00ff : 0xffffffff;
    renderer_text(position[e], 1, true, true, color, 0, "%s", tag[e]);
  }
}
