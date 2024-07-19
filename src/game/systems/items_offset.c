#include "engine/ecs.h"
#include "engine/types.h"
#include "game/components.h"
#include "general/core.h"
#include "general/global.h"

void
system_items_offset(usize entities_amount) {
  if (global.game.menu_type != IGM_INVENTORY) return;
  u32 *id = ecs_get_component_list("cursor-id");
  for (Entity e = 0; e < entities_amount; e++) {
    if (id[e] != global.game.items_cursor_id) continue;
    if (global.menu.option_id[id[e]] < global.game.items_cursor_min) {
      global.game.items_cursor_min--;
      global.game.items_cursor_max--;
      global.game.items_offset -= 1 + PX_TO_UNIT * 3;
    } else if (global.menu.option_id[id[e]] > global.game.items_cursor_max) {
      global.game.items_cursor_min++;
      global.game.items_cursor_max++;
      global.game.items_offset += 1 + PX_TO_UNIT * 3;
    }
  }
}
