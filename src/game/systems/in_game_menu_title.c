#include "engine/ecs.h"
#include "engine/math.h"
#include "engine/renderer.h"
#include "engine/types.h"
#include "game/components.h"
#include "general/core.h"
#include "general/global.h"

void
system_in_game_menu_title(usize entities_amount) {
  for (Entity e = 0; e < entities_amount; e++) {
    const char *title;
    switch (global.game.menu_type) {
      case IGM_NONE:
        title = 0;
        break;
      case IGM_PAUSE:
        title = "~ PAUSED ~";
        break;
      case IGM_INVENTORY:
        title = "~ INVENTORY ~";
        break;
      case IGM_ABILITIES:
        title = "~ ABILITIES ~";
        break;
      case IGM_SPELLS:
        title = "~ SPELLS ~";
        break;
    }
    if (title) {
      global.game.inventory_y = UI_TOP - 1;
      renderer_text(V2F(0, global.game.inventory_y - PX_TO_UNIT), 1, true, false, 0xff5500ff, 1, "%s", title);
      renderer_text(V2F(0, global.game.inventory_y), 1, true, false, 0xffffaaff, 1, "%s", title);
    }
  }
}
