#include "engine/ecs.h"
#include "engine/math.h"
#include "engine/renderer.h"
#include "engine/types.h"
#include "general/global.h"
#include "general/core.h"
#include "game/components.h"

void
system_draw_item(usize entities_amount) {
  Item *item = ecs_get_component_list("item");
  for (Entity e = 0; e < entities_amount; e++) {
    f32 y = global.game.inventory_y - (1 + PX_TO_UNIT * 3) * (item[e].id + 1);
    if (item[e].id > global.game.items_cursor_max || item[e].id < global.game.items_cursor_min) {
      continue;
    }
    Color bg = 0x000000ff;
    Color fg = 0xffffffff;
    Layer layer = 0;
    if (global.menu.option_id[global.game.items_cursor_id] == item[e].id) { bg ^= fg; fg ^= bg; bg ^= fg; layer = 1; }
    renderer_rect(V2F(UI_LEFT - PX_TO_UNIT * 2, y + PX_TO_UNIT * 2 + global.game.items_offset), V2F(UI_W + PX_TO_UNIT * 4, 1 + PX_TO_UNIT * 4), false, 0xffffffff, layer);
    renderer_rect(V2F(UI_LEFT - PX_TO_UNIT * 1, y + PX_TO_UNIT * 1 + global.game.items_offset), V2F(UI_W + PX_TO_UNIT * 2, 1 + PX_TO_UNIT * 2), false, bg, layer);
    renderer_rect(V2F(UI_RIGHT - 2.0f, y + PX_TO_UNIT * 2 + global.game.items_offset), V2F(PX_TO_UNIT, 1 + PX_TO_UNIT * 4), false, fg, layer);
    renderer_text(V2F(UI_LEFT + PX_TO_UNIT, y + global.game.items_offset), 1, false, false, fg, layer, "%.*s", item[e].name_size, item[e].name_buff);
    renderer_text(V2F(UI_RIGHT - 1.5f - PX_TO_UNIT, y + global.game.items_offset), 1, false, false, fg, layer, "%.2u", item[e].weight);
  }
}
