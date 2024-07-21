#include "general/global.h"
#include "engine/scene_manager.h"
#include "game/prefabs.h"

static void
cancel_option(void) {
  scene_manager_goto("save-slots-menu");
}

void
scene_delete_save_menu_on_start(void) {
  global.all.split_screen = false;
  global.menu.cursor_id = 0;
  global.menu.cursor_id_prv = 0;
  global.menu.option_id[0] = 3;
  global.menu.option_amount[0] = 0;
  V2f position = { 0.0f, 3.0f };
  prefab_save_slot(position, global.menu.option_amount[0]++, 0);
  position.y -= 2;
  prefab_save_slot(position, global.menu.option_amount[0]++, 0);
  position.y -= 2;
  prefab_save_slot(position, global.menu.option_amount[0]++, 0);
  position.y -= 3;
  prefab_menu_option(position, "Cancel", (Callback)cancel_option, 0, global.menu.option_amount[0]++, 0, true);
  prefab_menu_cursor(0, false, true);
}

void
scene_delete_save_menu_on_pre_systems(void) {
  global.menu.cursor_id_prv = global.menu.cursor_id;
}
