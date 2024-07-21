#include "general/core.h"
#include "general/global.h"
#include "engine/tilemap.h"
#include "game/prefabs.h"

void
scene_overworld_on_start(void) {
  global.all.split_screen = true;
  global.game.items_amount = 0;
  global.game.deleted_item = false;
  tilemap_setup(GAME_W, GAME_H);
  prefab_terminal();
  prefab_player(V2FS(1));
  prefab_all_items();
  prefab_pause();
}

void
scene_overworld_on_update(void) {
  global.menu.cursor_id_prv = global.menu.cursor_id;
  global.game.menu_type_prv = global.game.menu_type;
  if (global.game.menu_type == IGM_INVENTORY) {
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
}
