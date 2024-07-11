#include "include/core.h"
#include "include/global.h"
#include "include/prefabs.h"

void
save_slots_menu_scene(void) {
  global.split_screen = false;
  global.option_id = 0;
  V2f position = { 0 };
  prefab_save_slot(position, 0);
  position.y -= 2;
  prefab_save_slot(position, 1);
  position.y -= 2;
  prefab_save_slot(position, 2);
  prefab_menu_cursor(3);
}
