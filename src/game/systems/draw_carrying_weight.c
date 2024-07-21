#include "engine/ecs.h"
#include "engine/math.h"
#include "engine/renderer.h"
#include "game/components.h"
#include "general/core.h"
#include "general/global.h"

void
system_draw_carrying_weight(usize entities_amount) {
  CharacterSheet *character_sheet = ecs_get_component_list("character-sheet");
  for (Entity e = 0; e < entities_amount; e++) {
    global.game.inventory_y -= 3;
    renderer_rect(V2F(0, global.game.inventory_y), V2F(10.75f + PX_TO_UNIT * 5, 2 + PX_TO_UNIT * 4), true, 0xffffffff, 1);
    renderer_rect(V2F(0, global.game.inventory_y), V2F(10.75f + PX_TO_UNIT * 3, 2 + PX_TO_UNIT * 2), true, 0x000000ff, 1);
    renderer_text(V2F(0.125f, global.game.inventory_y + 1), 1, true, false, 0xffffffff, 1, "@ Carrying Weight");
    renderer_text(V2F(0, global.game.inventory_y), 1, true, false, 0xffff00ff, 1, "%.3u/%.3u", character_sheet->carrying_weight_cur, character_sheet->carrying_weight_max);
    global.game.inventory_y -= 3;
  }
}
