#include "include/components.h"
#include "include/core.h"
#include "include/ecs.h"
#include "include/global.h"
#include "include/math.h"
#include "include/prefabs.h"
#include "include/scene_manager.h"
#include "include/scenes.h"
#include "include/serialization.h"
#include <stdio.h>
#include <string.h>

static EntityReference new_character;

static void
get_character_name(CharacterName *name) {
  CharacterName *nc_name = ecs_entity_reference_get_component(new_character, "character-name");
  memcpy(nc_name->buff, name->buff, name->size);
  nc_name->size = name->size;
}

static void
class_option(void) {
  global.menu.cursor_id = 1;
}

static void
choose_class_option(CallbackArg class) {
  Class *nc_class = ecs_entity_reference_get_component(new_character, "class");
  *nc_class = (uptr)class;
  global.menu.cursor_id = 0;
  global.character_creation.class = (uptr)class;
}

static void
get_agility(i32 *agility) {
  Attributes *attributes = ecs_entity_reference_get_component(new_character, "attributes");
  attributes->agility = *agility;
}

static void
get_intelect(i32 *intelect) {
  Attributes *attributes = ecs_entity_reference_get_component(new_character, "attributes");
  attributes->intelect = *intelect;
}

static void
get_presence(i32 *presence) {
  Attributes *attributes = ecs_entity_reference_get_component(new_character, "attributes");
  attributes->presence = *presence;
}

static void
get_strength(i32 *strength) {
  Attributes *attributes = ecs_entity_reference_get_component(new_character, "attributes");
  attributes->strength = *strength;
}

static void
get_vigor(i32 *vigor) {
  Attributes *attributes = ecs_entity_reference_get_component(new_character, "attributes");
  attributes->vigor = *vigor;
}

static void
attributes_option(void) {
  global.menu.cursor_id = 2;
}

static void
begin_adventure_option(void) {
  if (!global.character_creation.has_name || global.character_creation.total_attribute_points > 0 || global.character_creation.class == CLASS_UNKNOWN) return;
  CharacterName *name = ecs_entity_reference_get_component(new_character, "character-name");
  Class *class = ecs_entity_reference_get_component(new_character, "class");
  Attributes *attributes = ecs_entity_reference_get_component(new_character, "attributes");
  DefensiveStats defensive_stats;
  CharacterSheet character_sheet;
  character_sheet.level              = 0;
  character_sheet.experience         = 0;
  defensive_stats.armour_points      = 6;
  defensive_stats.hit_points_max     = 20 + (attributes->vigor + attributes->strength) * 3;
  defensive_stats.hit_points_cur     = defensive_stats.hit_points_max;
  character_sheet.food_points_max    = 49 + attributes->vigor * 10;
  character_sheet.food_points_cur    = character_sheet.food_points_max;
  character_sheet.essence_points_max = 10 + (attributes->intelect + attributes->presence) * 2;
  character_sheet.essence_points_cur = character_sheet.essence_points_max;
  serialization_start();
  deserialize(CHARACTER_SHEET_NAME_SIZE,          &name->size);
  deserialize(CHARACTER_SHEET_NAME_BUFF,           name->buff);
  deserialize(CHARACTER_SHEET_CLASS,               class);
  deserialize(CHARACTER_SHEET_ATTRIBUTE_AGI,      &attributes->agility);
  deserialize(CHARACTER_SHEET_ATTRIBUTE_INT,      &attributes->intelect);
  deserialize(CHARACTER_SHEET_ATTRIBUTE_PRE,      &attributes->presence);
  deserialize(CHARACTER_SHEET_ATTRIBUTE_STR,      &attributes->strength);
  deserialize(CHARACTER_SHEET_ATTRIBUTE_VIG,      &attributes->vigor);
  deserialize(CHARACTER_SHEET_LEVEL,              &character_sheet.level);
  deserialize(CHARACTER_SHEET_EXPERIENCE,         &character_sheet.experience);
  deserialize(CHARACTER_SHEET_ARMOUR_POINTS,      &defensive_stats.armour_points);
  deserialize(CHARACTER_SHEET_HIT_POINTS_MAX,     &defensive_stats.hit_points_max);
  deserialize(CHARACTER_SHEET_HIT_POINTS_CUR,     &defensive_stats.hit_points_cur);
  deserialize(CHARACTER_SHEET_FOOD_POINTS_MAX,    &character_sheet.food_points_max);
  deserialize(CHARACTER_SHEET_FOOD_POINTS_CUR,    &character_sheet.food_points_cur);
  deserialize(CHARACTER_SHEET_ESSENCE_POINTS_MAX, &character_sheet.essence_points_max);
  deserialize(CHARACTER_SHEET_ESSENCE_POINTS_CUR, &character_sheet.essence_points_cur);
  scene_manager_goto_scene(overworld_scene);
}

static void
go_back_option(void) {
  ecs_entity_clean_reference(&new_character);
  scene_manager_goto_scene(save_slots_menu_scene);
}

void
character_creation_scene(void) {
  global.all.split_screen = false;
  global.character_creation.total_attribute_points = 5;
  global.character_creation.has_name = false;
  global.character_creation.class = CLASS_UNKNOWN;
  global.character_creation.class_prv = CLASS_UNKNOWN;
  global.menu.option_id[0] = 0;
  global.menu.option_id[1] = 3;
  global.menu.option_id[2] = 0;
  global.menu.cursor_id = 0;
  global.menu.cursor_id_prv = 0;
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
  position.y -= 2.0f;
  prefab_menu_option(position, "Go Back", (Callback)go_back_option, 0, 4, 0);
  prefab_menu_cursor(5, 0, false);
  prefab_menu_cursor(3, 1, true);
  prefab_menu_cursor(5, 2, true);
  prefab_menu_hint(V2F(0, SCREEN_BOTTOM + 2));
}
