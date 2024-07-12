#include "include/core.h"
#include "include/global.h"
#include "include/prefabs.h"
#include "include/scene_manager.h"
#include "include/window.h"
#include "include/scenes.h"

static void
start_option(void) {
  scene_manager_goto_scene(save_slots_menu_scene);
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
main_menu_scene(void) {
  global.split_screen = false;
  global.option_id[0] = 0;
  global.cursor_id = 0;
  V2f position = { 0.0f, 2.5f };
  prefab_menu_option(position, "Start", start_option, 0, 0);
  position.y -= 2;
  prefab_menu_option(position, "Help", help_option, 1, 0);
  position.y -= 2;
  prefab_menu_option(position, "Exit", exit_option, 2, 0);
  prefab_menu_cursor(3, 0, false);
}
