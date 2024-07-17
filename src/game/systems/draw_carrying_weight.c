#include "engine/ecs.h"
#include "engine/math.h"
#include "engine/renderer.h"
#include "game/components.h"
#include "general/core.h"
#include "general/global.h"

void
system_draw_carrying_weight(void) {
  CharacterSheet *character_sheet = ecs_get_component_list("character-sheet");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (global.game.menu_type == IGM_INVENTORY) {
      renderer_rect(V2F(0, UI_TOP - 4), V2F(10.75f + PX_TO_UNIT * 4, 2 + PX_TO_UNIT * 4), true, 0xffffffff, 0);
      renderer_rect(V2F(0, UI_TOP - 4), V2F(10.75f + PX_TO_UNIT * 2, 2 + PX_TO_UNIT * 2), true, 0x000000ff, 0);
      renderer_text(V2F(0, UI_TOP - 3), 1, true, false, 0xffffffff, 0, "@ Carrying Weight");
      renderer_text(V2F(0, UI_TOP - 4), 1, true, false, 0xffff00ff, 0, "%.3u/%.3u", character_sheet->carrying_weight_cur, character_sheet->carrying_weight_max);
    }
  }
}
