#include "include/components.h"
#include "include/global.h"
#include "include/math.h"
#include "include/prefabs.h"

static void
class_option(void) {
  global.cursor_id = 1;
}

static void
choose_class_option(OptionCallbackArg class) {
  global.cursor_id = 0;
  global.class = (uptr)class;
}

static void
attributes_option(void) {
  global.cursor_id = 2;
}

void
character_creation_scene(void) {
  global.split_screen = false;
  global.attribute_points = 5;
  global.class = CLASS_UNKNOWN;
  global.class_prv = CLASS_UNKNOWN;
  global.option_id[0] = 0;
  global.option_id[1] = 3;
  global.option_id[2] = 0;
  global.cursor_id = 0;
  global.cursor_id_prv = 0;
  V2f position = { 0, 6 };
  prefab_character_name_input(position, 0, 0);
  position.y -= 2;
  prefab_menu_option(position, "Choose a Class", (OptionCallback)class_option, 0, 1, 0);
  position.y -= 1;
  prefab_menu_option(V2F(-05.0f, position.y), "Fighter", (OptionCallback)choose_class_option, (OptionCallbackArg)CLASS_FIGHTER, 0, 1);
  prefab_menu_option(V2F(+00.0f, position.y), "Thief", (OptionCallback)choose_class_option, (OptionCallbackArg)CLASS_THIEF, 1, 1);
  prefab_menu_option(V2F(+05.0f, position.y), "Wizard", (OptionCallback)choose_class_option, (OptionCallbackArg)CLASS_WIZARD, 2, 1);
  position.y -= 2;
  prefab_menu_option_with_u32_arg(position, "Attribute Points: ", (OptionCallback)attributes_option, 0, 2, 0, 0, "total-attribute-points");
  position.y -= 1;
  prefab_attribute_input(V2F(-14.0f, position.y), ATT_AGILITY,  0, 2);
  prefab_attribute_input(V2F(-07.0f, position.y), ATT_INTELECT, 1, 2);
  prefab_attribute_input(V2F(+00.0f, position.y), ATT_PRESENCE, 2, 2);
  prefab_attribute_input(V2F(+07.0f, position.y), ATT_STRENGTH, 3, 2);
  prefab_attribute_input(V2F(+14.0f, position.y), ATT_VIGOR,    4, 2);
  prefab_menu_cursor(3, 0, false);
  prefab_menu_cursor(3, 1, true);
  prefab_menu_cursor(5, 2, true);
}
