#include "game/components.h"
#include "general/global.h"
#include "engine/ecs.h"
#include "engine/renderer.h"

static const char *class_names[] = { "Fighter", "Thief", "Wizard" };

void
system_draw_save_slot(void) {
  CharacterName *character_name = ecs_get_component_list("character-name");
  Class *class = ecs_get_component_list("class");
  V2f *position = ecs_get_component_list("position");
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
    if (character_name[e].size) {
      renderer_text(position[e], 1, true, true, color, 0, "%s%.*s, The %s%s", select_start, character_name[e].size, character_name[e].buff, class_names[class[e]], select_end);
    } else {
      renderer_text(position[e], 1, true, true, color, 0, "%sNew Game%s", select_start, select_end);
    }
  }
}
