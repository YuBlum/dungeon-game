#include "include/global.h"
#include "include/math.h"
#include "include/prefabs.h"

static void
class_option(void) {
  global.cursor_id = 1;
}

static void
choose_class_option(void) {
  global.cursor_id = 0;
}

static void
attributes_option(void) {
}

void
character_creation_scene(void) {
  global.split_screen = false;
  global.option_id[0] = 0;
  global.option_id[1] = 0;
  V2f position = { 0, 0 };
  prefab_character_name_input(position, 0, 0);
  position.y -= 2;
  prefab_menu_option(V2F(-08.5f, position.y), "CLASS:", class_option, 1, 0);
  prefab_menu_option(V2F(-03.0f, position.y), "Fighter", choose_class_option, 0, 1);
  prefab_menu_option(V2F(+01.5f, position.y), "Thief", choose_class_option, 1, 1);
  prefab_menu_option(V2F(+06.0f, position.y), "Wizard", choose_class_option, 2, 1);
  position.y -= 2;
  prefab_menu_option(position, "Attributes", attributes_option, 2, 0);
  prefab_menu_cursor(3, 0, false);
  prefab_menu_cursor(3, 1, true);
}
