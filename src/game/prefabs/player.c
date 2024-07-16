#include "game/components.h"
#include "engine/math.h"
#include "engine/renderer.h"
#include "engine/serialization.h"
#include "engine/tilemap.h"
#include "general/global.h"

void
prefab_player(V2f position) {
  position = tilemap_snap_to_grid(position);
  CharacterName name;
  Attributes attributes;
  CharacterSheet character_sheet;
  DefensiveStats defensive_stats;
  deserialize(CHARACTER_SHEET_NAME_SIZE,          &name.size);
  deserialize(CHARACTER_SHEET_NAME_BUFF,           name.buff);
  deserialize(CHARACTER_SHEET_CLASS,              &global.game.class);
  deserialize(CHARACTER_SHEET_ATTRIBUTE_AGI,      &attributes.agility);
  deserialize(CHARACTER_SHEET_ATTRIBUTE_INT,      &attributes.intelect);
  deserialize(CHARACTER_SHEET_ATTRIBUTE_PRE,      &attributes.presence);
  deserialize(CHARACTER_SHEET_ATTRIBUTE_STR,      &attributes.strength);
  deserialize(CHARACTER_SHEET_ATTRIBUTE_VIG,      &attributes.vigor);
  deserialize(CHARACTER_SHEET_GOLD,               &character_sheet.gold);
  deserialize(CHARACTER_SHEET_LEVEL,              &character_sheet.level);
  deserialize(CHARACTER_SHEET_EXPERIENCE,         &character_sheet.experience);
  deserialize(CHARACTER_SHEET_ARMOUR_POINTS,      &defensive_stats.armour_points);
  deserialize(CHARACTER_SHEET_HIT_POINTS_MAX,     &defensive_stats.hit_points_max);
  deserialize(CHARACTER_SHEET_HIT_POINTS_CUR,     &defensive_stats.hit_points_cur);
  deserialize(CHARACTER_SHEET_FOOD_POINTS_MAX,    &character_sheet.food_points_max);
  deserialize(CHARACTER_SHEET_FOOD_POINTS_CUR,    &character_sheet.food_points_cur);
  deserialize(CHARACTER_SHEET_ESSENCE_POINTS_MAX, &character_sheet.essence_points_max);
  deserialize(CHARACTER_SHEET_ESSENCE_POINTS_CUR, &character_sheet.essence_points_cur);
  ecs_entity_creation_begin("position", "direction", "position-lerp", "speed", "color", "input", "bump", "attributes", "defensive-stats", "character-name", "character-sheet", "class");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(V2f, "direction", V2FS(0));
    ecs_entity_creation_setup_component(PositionLerp, "position-lerp", ((PositionLerp){ position, position, 1.0f }));
    ecs_entity_creation_setup_component(f32, "speed", 6.0f);
    ecs_entity_creation_setup_component(Color, "color", 0xffaa00ff);
    ecs_entity_creation_setup_component(bool, "bump", false);
    ecs_entity_creation_setup_component(Attributes, "attributes", attributes);
    ecs_entity_creation_setup_component(DefensiveStats, "defensive-stats", defensive_stats);
    ecs_entity_creation_setup_component(CharacterName, "character-name", name);
    ecs_entity_creation_setup_component(CharacterSheet, "character-sheet", character_sheet);
    ecs_entity_creation_setup_component(Class, "class", global.game.class);
  ecs_entity_creation_end();
}
