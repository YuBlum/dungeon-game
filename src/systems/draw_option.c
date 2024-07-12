#include "include/ecs.h"
#include "include/global.h"
#include "include/math.h"
#include "include/renderer.h"

void
draw_option_system(void) {
  V2f *position = ecs_get_component_list("position");
  const char **tag = ecs_get_component_list("tag");
  u32 *id = ecs_get_component_list("option-id");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    const char *fmt = "%s";
    Color color = 0xffffffff;
    if (id[e] == global.option_id[cursor_id[e]]) {
      color = 0xffff00ff;
      if (global.cursor_id == cursor_id[e]) fmt = "> %s <";
    }
    renderer_text(position[e], 1, true, true, color, 0, fmt, tag[e]);
  }
}
