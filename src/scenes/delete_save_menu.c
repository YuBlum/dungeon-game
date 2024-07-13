#include "include/global.h"
#include "include/prefabs.h"
#include "include/scene_manager.h"
#include "include/scenes.h"


static void
cancel_option(void) {
  scene_manager_goto_scene(save_slots_menu_scene);
}

void
delete_save_menu_scene(void) {
  global.all.split_screen = false;
  global.menu.option_id[0] = 0;
  global.menu.cursor_id = 0;
  global.menu.cursor_id_prv = 0;
  V2f position = { 0.0f, 3.0f };
  u32 cursor_id = 0;
  prefab_save_slot(position, cursor_id++, 0);
  position.y -= 2;
  prefab_save_slot(position, cursor_id++, 0);
  position.y -= 2;
  prefab_save_slot(position, cursor_id++, 0);
  position.y -= 3;
  prefab_menu_option(position, "Cancel", (Callback)cancel_option, 0, cursor_id++, 0);
  prefab_menu_cursor(cursor_id, 0, false);
}
