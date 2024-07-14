#include "general/core.h"
#include "general/global.h"
#include "engine/scene_manager.h"
#include "engine/window.h"
#include "game/prefabs.h"
#include "game/scenes.h"

static void
start_option(void) {
  scene_manager_goto(scene_save_slots_menu);
}

static void
help_option(void) {
  WARN("Not Implemented");
}

static void
exit_option(void) {
  window_destroy();
}

void
scene_main_menu(void) {
  global.all.split_screen = false;
  global.menu.option_id[0] = 0;
  global.menu.cursor_id = 0;
  global.menu.cursor_id_prv = 0;
  V2f position = { 0.0f, 2.5f };
  prefab_menu_option(position, "Start", (Callback)start_option, 0, 0, 0);
  position.y -= 2;
  prefab_menu_option(position, "Help", (Callback)help_option, 0, 1, 0);
  position.y -= 2;
  prefab_menu_option(position, "Exit", (Callback)exit_option, 0, 2, 0);
  prefab_menu_cursor(3, 0, false);
}
