#include "include/components.h"
#include "include/ecs.h"
#include "include/global.h"
#include "include/math.h"
#include "include/renderer.h"
#include "include/core.h"

void
draw_character_name_input_system(void) {
  V2f *position = ecs_get_component_list("position");
  CharacterName *character_name = ecs_get_component_list("character-name");
  u32 *id = ecs_get_component_list("option-id");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    V2f pos = v2f_add(position[e], V2F(-PX_TO_UNIT, PX_TO_UNIT));
    Color color =  0xffffffff;
    if (id[e] == global.option_id[cursor_id[e]]) {
      color = 0xffff00ff;
      if (global.cursor_id == cursor_id[e]) {
        renderer_text(v2f_sub(pos, V2F(CHARACTER_NAME_CAP * 0.5f + 10*PX_TO_UNIT, 0)), 1, true, true, color, 1, ">");
        renderer_text(v2f_add(pos, V2F(CHARACTER_NAME_CAP * 0.5f + 10*PX_TO_UNIT, 0)), 1, true, true, color, 1, "<");
      }
    }
    renderer_rect(pos, V2F(CHARACTER_NAME_CAP+PX_TO_UNIT*2, 1+PX_TO_UNIT*2), true, color, 0);
    renderer_rect(pos, V2F(CHARACTER_NAME_CAP, 1), true, 0x000000ff, 0);
    if (character_name[e].size) {
      renderer_text(pos, 1, true, true, color, 0, "%.*s", character_name[e].size, character_name[e].buff);
    } else {
      renderer_text(pos, 1, true, true, 0x555555ff, 0, "Name Here");
    }
  }
}
