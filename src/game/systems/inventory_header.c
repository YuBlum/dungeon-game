#include "engine/ecs.h"
#include "engine/math.h"
#include "engine/renderer.h"
#include "engine/types.h"
#include "general/global.h"
#include "general/core.h"
#include "game/components.h"

void
system_inventory_header(void) {
  if (global.game.menu_type != IGM_INVENTORY) return;
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    global.game.inventory_y -= 2;
    renderer_rect(V2F(UI_LEFT - PX_TO_UNIT * 2, global.game.inventory_y + PX_TO_UNIT * 2), V2F(UI_W + PX_TO_UNIT * 4, 1 + PX_TO_UNIT * 4), false, 0xffffffff, 1);
    renderer_rect(V2F(UI_LEFT - PX_TO_UNIT * 1, global.game.inventory_y + PX_TO_UNIT * 1), V2F(UI_W + PX_TO_UNIT * 2, 1 + PX_TO_UNIT * 2), false, 0x000000ff, 1);
    renderer_rect(V2F(UI_RIGHT - 2.0f, global.game.inventory_y + PX_TO_UNIT), V2F(PX_TO_UNIT, 1 + PX_TO_UNIT * 2), false, 0xffffffff, 1);
    renderer_text(V2F(UI_RIGHT - 1.625f, global.game.inventory_y), 1, false, false, 0xffffffff, 1, "@");
    renderer_text(V2F(UI_LEFT + (UI_W - 2.0f) * 0.5f - 1.5f, global.game.inventory_y), 1, false, false, 0xffffffff, 1, "Name");
  }
}
