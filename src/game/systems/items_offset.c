#include "engine/ecs.h"
#include "engine/types.h"
#include "game/components.h"
#include "general/core.h"
#include "general/global.h"

void
system_items_offset(void) {
  if (global.game.menu_type != IGM_INVENTORY) return;
  u32 *id = ecs_get_component_list("cursor-id");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (id[e] != 0) continue;
    if (global.menu.option_id[id[e]] > 3) {
      global.game.items_offset = (global.menu.option_id[id[e]] - 3) * (1 + PX_TO_UNIT * 3);
    } else {
      global.game.items_offset = 0;
    }
  }
}
