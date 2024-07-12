#include "include/global.h"
#include "include/prefabs.h"
#include "include/scene_manager.h"
#include "include/scenes.h"

static void
go_back_option(void) {
  scene_manager_goto_scene(main_menu_scene);
}

void
save_slots_menu_scene(void) {
  global.split_screen = false;
  global.option_id[0] = 0;
  global.cursor_id = 0;
  global.cursor_id_prv = 0;
  V2f position = { 0.0f, 3.0f };
  prefab_save_slot(position, 0, 0);
  position.y -= 2;
  prefab_save_slot(position, 1, 0);
  position.y -= 2;
  prefab_save_slot(position, 2, 0);
  position.y -= 2;
  prefab_menu_option(position, "Go Back", (OptionCallback)go_back_option, 0, 3, 0);
  prefab_menu_cursor(4, 0, false);
}
