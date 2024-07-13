#include "include/components.h"
#include "include/ecs.h"
#include "include/global.h"
#include "include/math.h"
#include "include/renderer.h"

void
draw_option_system(void) {
  V2f *position = ecs_get_component_list("position");
  Tag *tag = ecs_get_component_list("tag");
  u32 *id = ecs_get_component_list("option-id");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    Color color = 0xffffffff;
    char *select_start = "";
    char *select_end = "";
    if (id[e] == global.menu.option_id[cursor_id[e]]) {
      color = 0xffff00ff;
      if (global.menu.cursor_id == cursor_id[e]) {
        select_start = "> ";
        select_end = " <";
      }
    }
    renderer_text(position[e], 1, true, true, color, 0, "%s%s%s", select_start, tag[e], select_end);
  }
}

void
draw_option_with_u32_arg_system(void) {
  V2f *position = ecs_get_component_list("position");
  Tag *tag = ecs_get_component_list("tag");
  u32 *id = ecs_get_component_list("option-id");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  u32 *u32_arg = ecs_get_component_list("u32-arg");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    Color color = 0xffffffff;
    char *select_start = "";
    char *select_end = "";
    if (id[e] == global.menu.option_id[cursor_id[e]]) {
      color = 0xffff00ff;
      if (global.menu.cursor_id == cursor_id[e]) {
        select_start = "> ";
        select_end = " <";
      }
    }
    renderer_text(position[e], 1, true, true, color, 0, "%s%s%u%s", select_start, tag[e], u32_arg[e], select_end);
  }
}
