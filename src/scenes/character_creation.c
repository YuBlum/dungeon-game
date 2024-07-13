#include "include/components.h"
#include "include/core.h"
#include "include/ecs.h"
#include "include/global.h"
#include "include/math.h"
#include "include/prefabs.h"
#include "include/scene_manager.h"
#include "include/scenes.h"
#include <stdio.h>

static EntityReference new_character;

static void
get_character_name(CharacterName *name) {
  CharacterName *nc_name = ecs_entity_reference_get_component(new_character, "character-name");
  *nc_name = *name;
  INFO("%.*s", name->size, name->buff);
}

static void
class_option(void) {
  global.cursor_id = 1;
}

static void
choose_class_option(CallbackArg class) {
  Class *nc_class = ecs_entity_reference_get_component(new_character, "class");
  *nc_class = (uptr)class;
  global.cursor_id = 0;
  global.class = (uptr)class;
  INFO("%d", *nc_class);
}

static void
get_agility(i32 *agility) {
  Attributes *attributes = ecs_entity_reference_get_component(new_character, "attributes");
  attributes->agility = *agility;
  INFO("agility: %d", attributes->agility);
}

static void
get_intelect(i32 *intelect) {
  Attributes *attributes = ecs_entity_reference_get_component(new_character, "attributes");
  attributes->intelect = *intelect;
  INFO("intelect: %d", attributes->intelect);
}

static void
get_presence(i32 *presence) {
  Attributes *attributes = ecs_entity_reference_get_component(new_character, "attributes");
  attributes->presence = *presence;
  INFO("presence: %d", attributes->presence);
}

static void
get_strength(i32 *strength) {
  Attributes *attributes = ecs_entity_reference_get_component(new_character, "attributes");
  attributes->strength = *strength;
  INFO("strength %d", attributes->strength);
}

static void
get_vigor(i32 *vigor) {
  Attributes *attributes = ecs_entity_reference_get_component(new_character, "attributes");
  attributes->vigor = *vigor;
  INFO("vigor: %d", attributes->vigor);
}

static void
attributes_option(void) {
  global.cursor_id = 2;
}

static void
begin_adventure_option(void) {
  if (!global.has_name || global.total_attribute_points > 0 || global.class == CLASS_UNKNOWN) return;
  CharacterName *name = ecs_entity_reference_get_component(new_character, "character-name");
  Class *class = ecs_entity_reference_get_component(new_character, "class");
  Attributes *attributes = ecs_entity_reference_get_component(new_character, "attributes");
  char path[SAVE_PATH_SIZE];
  snprintf(path, SAVE_PATH_SIZE, SAVE_PATH_FMT, global.save_slot);
  FILE *f = fopen(path, "wb");
#if DEVMODE
  if (!f) ERROR("couldn't create file");
#endif
  fwrite(&name->size, sizeof (u32), 1, f);
  fwrite(name->buff, sizeof (char), name->size, f);
  fwrite(class, sizeof (Class), 1, f);
  fwrite(attributes, sizeof (Attributes), 1, f);
  fclose(f);
  scene_manager_goto_scene(scene_test0);
}

void
character_creation_scene(void) {
  global.split_screen = false;
  global.total_attribute_points = 5;
  global.has_name = false;
  global.class = CLASS_UNKNOWN;
  global.class_prv = CLASS_UNKNOWN;
  global.option_id[0] = 0;
  global.option_id[1] = 3;
  global.option_id[2] = 0;
  global.cursor_id = 0;
  global.cursor_id_prv = 0;
  prefab_new_character(&new_character);
  V2f position = { 0, 6 };
  prefab_character_name_input(position, 0, 0, (Callback)get_character_name);
  position.y -= 2;
  prefab_menu_option(position, "Class", (Callback)class_option, 0, 1, 0);
  position.y -= 1;
  prefab_menu_option(V2F(-05.0f, position.y), "Fighter", (Callback)choose_class_option, (CallbackArg)CLASS_FIGHTER, 0, 1);
  prefab_menu_option(V2F(+00.0f, position.y), "Thief", (Callback)choose_class_option, (CallbackArg)CLASS_THIEF, 1, 1);
  prefab_menu_option(V2F(+05.0f, position.y), "Wizard", (Callback)choose_class_option, (CallbackArg)CLASS_WIZARD, 2, 1);
  position.y -= 2;
  prefab_menu_option_with_u32_arg(position, "Attribute Points: ", (Callback)attributes_option, 0, 2, 0, 0, "total-attribute-points");
  position.y -= 1;
  prefab_attribute_input(V2F(-14.0f, position.y), ATT_AGILITY,  0, 2, (Callback)get_agility);
  prefab_attribute_input(V2F(-07.0f, position.y), ATT_INTELECT, 1, 2, (Callback)get_intelect);
  prefab_attribute_input(V2F(+00.0f, position.y), ATT_PRESENCE, 2, 2, (Callback)get_presence);
  prefab_attribute_input(V2F(+07.0f, position.y), ATT_STRENGTH, 3, 2, (Callback)get_strength);
  prefab_attribute_input(V2F(+14.0f, position.y), ATT_VIGOR,    4, 2, (Callback)get_vigor);
  position.y -= 4.5f;
  prefab_menu_option(position, "Begin Adventure", (Callback)begin_adventure_option, 0, 3, 0);
  prefab_menu_cursor(4, 0, false);
  prefab_menu_cursor(3, 1, true);
  prefab_menu_cursor(5, 2, true);
  prefab_menu_hint(V2F(0, SCREEN_BOTTOM + 2));
}
