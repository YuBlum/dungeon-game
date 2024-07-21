#include "engine/types.h"
#include "game/components.h"
#include "general/core.h"
#include "general/global.h"
#include "engine/tilemap.h"
#include "game/prefabs.h"

void
scene_overworld_on_start(void) {
  global.all.split_screen = true;
  global.game.items_amount = 0;
  global.game.removed_item = false;
  global.game.fixed_items_order = false;
  tilemap_setup(GAME_W, GAME_H);
  prefab_terminal();
  prefab_player(V2FS(1));
  prefab_item(ITEM_WOOD_SWORD, 0);
  prefab_item(ITEM_WOOD_SHIELD, 0);
  prefab_pause();
}

void
scene_overworld_on_pre_systems(void) {
  global.menu.cursor_id_prv = global.menu.cursor_id;
  global.game.menu_type_prv = global.game.menu_type;
  if (global.game.menu_type == IGM_INVENTORY) {
    if (global.game.fixed_items_order) {
      global.game.removed_item = false;
      global.game.fixed_items_order = false;
    }
    global.menu.option_amount[global.game.items_cursor_id] = global.game.items_amount;
    if (global.menu.option_id[global.game.items_cursor_id] == global.game.items_amount) {
      global.menu.option_id[global.game.items_cursor_id]--;
    }
  }
}

void
scene_overworld_on_draw(void) {
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

  if (global.game.menu_type == IGM_INVENTORY) {
    f32 y = global.game.inventory_y - 6;
    renderer_rect(V2F(UI_LEFT - PX_TO_UNIT * 2, y + PX_TO_UNIT * 2), V2F(UI_W + PX_TO_UNIT * 4, 1 + PX_TO_UNIT * 4), false, 0xffffffff, 1);
    renderer_rect(V2F(UI_LEFT - PX_TO_UNIT * 1, y + PX_TO_UNIT * 1), V2F(UI_W + PX_TO_UNIT * 2, 1 + PX_TO_UNIT * 2), false, 0x000000ff, 1);
    renderer_rect(V2F(UI_RIGHT - 2.0f, y + PX_TO_UNIT), V2F(PX_TO_UNIT, 1 + PX_TO_UNIT * 2), false, 0xffffffff, 1);
    renderer_text(V2F(UI_RIGHT - 1.625f, y - PX_TO_UNIT), 1, false, false, 0xff5500ff, 1, "@");
    renderer_text(V2F(UI_LEFT + (UI_W - 2.0f) * 0.5f - 1.5f, y - PX_TO_UNIT), 1, false, false, 0xff5500ff, 1, "Name");
    renderer_text(V2F(UI_RIGHT - 1.625f, y), 1, false, false, 0xffffaaff, 1, "@");
    renderer_text(V2F(UI_LEFT + (UI_W - 2.0f) * 0.5f - 1.5f, y), 1, false, false, 0xffffaaff, 1, "Name");
  }
}
