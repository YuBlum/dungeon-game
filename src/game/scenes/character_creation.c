#include "general/core.h"
#include "general/global.h"
#include "engine/ecs.h"
#include "engine/math.h"
#include "engine/scene_manager.h"
#include "engine/serialization.h"
#include "game/scenes.h"
#include "game/prefabs.h"
#include "game/components.h"
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
  character_sheet.gold               = 0;
  serialization_start();
  serialize(CHARACTER_SHEET_NAME_SIZE,          &name->size);
  serialize(CHARACTER_SHEET_NAME_BUFF,           name->buff);
  serialize(CHARACTER_SHEET_CLASS,               class);
  serialize(CHARACTER_SHEET_ATTRIBUTE_AGI,      &attributes->agility);
  serialize(CHARACTER_SHEET_ATTRIBUTE_INT,      &attributes->intelect);
  serialize(CHARACTER_SHEET_ATTRIBUTE_PRE,      &attributes->presence);
  serialize(CHARACTER_SHEET_ATTRIBUTE_STR,      &attributes->strength);
  serialize(CHARACTER_SHEET_ATTRIBUTE_VIG,      &attributes->vigor);
  serialize(CHARACTER_SHEET_GOLD,               &character_sheet.gold);
  serialize(CHARACTER_SHEET_LEVEL,              &character_sheet.level);
  serialize(CHARACTER_SHEET_EXPERIENCE,         &character_sheet.experience);
  serialize(CHARACTER_SHEET_ARMOUR_POINTS,      &defensive_stats.armour_points);
  serialize(CHARACTER_SHEET_HIT_POINTS_MAX,     &defensive_stats.hit_points_max);
  serialize(CHARACTER_SHEET_HIT_POINTS_CUR,     &defensive_stats.hit_points_cur);
  serialize(CHARACTER_SHEET_FOOD_POINTS_MAX,    &character_sheet.food_points_max);
  serialize(CHARACTER_SHEET_FOOD_POINTS_CUR,    &character_sheet.food_points_cur);
  serialize(CHARACTER_SHEET_ESSENCE_POINTS_MAX, &character_sheet.essence_points_max);
  serialize(CHARACTER_SHEET_ESSENCE_POINTS_CUR, &character_sheet.essence_points_cur);
  scene_manager_goto(scene_overworld);
}

static void
go_back_option(void) {
  ecs_entity_clean_reference(&new_character);
  scene_manager_goto(scene_save_slots_menu);
}

void
scene_character_creation(void) {
  global.all.split_screen = false;
  global.character_creation.total_attribute_points = 5;
  global.character_creation.has_name = false;
  global.character_creation.class = CLASS_UNKNOWN;
  global.character_creation.class_prv = CLASS_UNKNOWN;
  global.menu.cursor_id = 0;
  global.menu.cursor_id_prv = 0;
  global.menu.option_id[0] = 0;
  global.menu.option_id[1] = 3;
  global.menu.option_id[2] = 0;
  global.menu.option_amount[0] = 0;
  global.menu.option_amount[1] = 0;
  global.menu.option_amount[2] = 0;
  prefab_new_character(&new_character);
  V2f position = { 0, 6 };
  prefab_character_name_input(position, global.menu.option_amount[0]++, 0, (Callback)get_character_name);
  position.y -= 2;
  prefab_menu_option(position, "Class", (Callback)class_option, 0, global.menu.option_amount[0]++, 0, true);
  position.y -= 1;
  prefab_menu_option(V2F(-05.0f, position.y), "Fighter", (Callback)choose_class_option, (CallbackArg)CLASS_FIGHTER, global.menu.option_amount[1]++, 1, true);
  prefab_menu_option(V2F(+00.0f, position.y), "Thief",   (Callback)choose_class_option, (CallbackArg)CLASS_THIEF,   global.menu.option_amount[1]++, 1, true);
  prefab_menu_option(V2F(+05.0f, position.y), "Wizard",  (Callback)choose_class_option, (CallbackArg)CLASS_WIZARD,  global.menu.option_amount[1]++, 1, true);
  position.y -= 2;
  prefab_menu_option_with_u32_arg(position, "Attribute Points: ", (Callback)attributes_option, 0, global.menu.option_amount[0]++, 0, true, 0, "total-attribute-points");
  position.y -= 1;
  prefab_attribute_input(V2F(-14.0f, position.y), ATT_AGILITY,  global.menu.option_amount[2]++, 2, (Callback)get_agility);
  prefab_attribute_input(V2F(-07.0f, position.y), ATT_INTELECT, global.menu.option_amount[2]++, 2, (Callback)get_intelect);
  prefab_attribute_input(V2F(+00.0f, position.y), ATT_PRESENCE, global.menu.option_amount[2]++, 2, (Callback)get_presence);
  prefab_attribute_input(V2F(+07.0f, position.y), ATT_STRENGTH, global.menu.option_amount[2]++, 2, (Callback)get_strength);
  prefab_attribute_input(V2F(+14.0f, position.y), ATT_VIGOR,    global.menu.option_amount[2]++, 2, (Callback)get_vigor);
  position.y -= 4.5f;
  prefab_menu_option(position, "Begin Adventure", (Callback)begin_adventure_option, 0, global.menu.option_amount[0]++, 0, true);
  position.y -= 2.0f;
  prefab_menu_option(position, "Go Back", (Callback)go_back_option, 0, global.menu.option_amount[0]++, 0, true);
  prefab_menu_cursor(0, false);
  prefab_menu_cursor(1, true);
  prefab_menu_cursor(2, true);
  prefab_menu_hint(V2F(0, SCREEN_BOTTOM + 2));
}
