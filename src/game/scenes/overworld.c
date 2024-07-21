#include "general/core.h"
#include "general/global.h"
#include "engine/tilemap.h"
#include "game/prefabs.h"

void
scene_overworld_on_start(void) {
  global.all.split_screen = true;
  global.game.items_amount = 0;
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
