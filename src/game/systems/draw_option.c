#include "game/components.h"
#include "general/global.h"
#include "engine/ecs.h"
#include "engine/math.h"
#include "engine/renderer.h"

void
system_draw_option(void) {
  V2f *position = ecs_get_component_list("position");
  Tag *tag = ecs_get_component_list("tag");
  u32 *id = ecs_get_component_list("option-id");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  bool *active = ecs_get_component_list("active");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (!active[e]) continue;
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
system_draw_option_with_u32_arg(void) {
  V2f *position = ecs_get_component_list("position");
  Tag *tag = ecs_get_component_list("tag");
  u32 *id = ecs_get_component_list("option-id");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  u32 *u32_arg = ecs_get_component_list("u32-arg");
  bool *active = ecs_get_component_list("active");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (!active[e]) continue;
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
