#include "include/components.h"
#include "include/core.h"
#include "include/ecs.h"
#include "include/global.h"
#include "include/math.h"
#include "include/renderer.h"
#include "include/tilemap.h"
#include <stdio.h>
#include "include/prefabs.h"

void
prefab_player(V2f position) {
  position = tilemap_snap_to_grid(position);
  CharacterName name;
  Class class;
  Attributes attributes;
  CharacterSheet character_sheet;
  DefensiveStats defensive_stats;
  char path[SAVE_PATH_SIZE];
  snprintf(path, SAVE_PATH_SIZE, SAVE_PATH_FMT, global.all.save_slot);
  FILE *f = fopen(path, "rb");
  if (!f) {
#if DEVMODE
    ERROR("Couldn't open '%s'", path);
#else
    exit(1);
#endif
  }
  fread(&name.size,                          sizeof (u32),   1,         f);
  fread(name.buff,                           sizeof (char),  name.size, f);
  fread(&class,                              sizeof (Class), 1,         f);
  fread(&attributes.agility,                 sizeof (i32),   1,         f);
  fread(&attributes.intelect,                sizeof (i32),   1,         f);
  fread(&attributes.presence,                sizeof (i32),   1,         f);
  fread(&attributes.strength,                sizeof (i32),   1,         f);
  fread(&attributes.vigor,                   sizeof (i32),   1,         f);
  fread(&character_sheet.level,              sizeof (u32),   1,         f);
  fread(&character_sheet.experience,         sizeof (u32),   1,         f);
  fread(&defensive_stats.armour_points,      sizeof (u32),   1,         f);
  fread(&defensive_stats.hit_points_max,     sizeof (u32),   1,         f);
  fread(&defensive_stats.hit_points_cur,     sizeof (u32),   1,         f);
  fread(&character_sheet.food_points_cur,    sizeof (u32),   1,         f);
  fread(&character_sheet.food_points_max,    sizeof (u32),   1,         f);
  fread(&character_sheet.essence_points_cur, sizeof (u32),   1,         f);
  fread(&character_sheet.essence_points_max, sizeof (u32),   1,         f);
  fclose(f);
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
    ecs_entity_creation_setup_component(Class, "class", class);
  ecs_entity_creation_end();
}

void
prefab_solid(V2f position) {
  position = tilemap_snap_to_grid(position);
  ecs_entity_creation_begin("position", "color");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(Color, "color", 0x00aa55ff);
  ecs_entity_creation_end();
}

void
prefab_menu_option(V2f position, Tag tag, Callback callback, CallbackArg callback_arg, u32 id, u32 cursor_id) {
  ecs_entity_creation_begin("position", "callback", "callback-arg", "tag", "option-id", "cursor-id");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(Callback, "callback", callback);
    ecs_entity_creation_setup_component(CallbackArg, "callback-arg", callback_arg);
    ecs_entity_creation_setup_component(Tag, "tag", tag);
    ecs_entity_creation_setup_component(u32, "option-id", id);
    ecs_entity_creation_setup_component(u32, "cursor-id", cursor_id);
  ecs_entity_creation_end();
}

void
prefab_menu_option_with_u32_arg(V2f position, Tag tag, Callback callback, CallbackArg callback_arg, u32 id, u32 cursor_id, u32 arg_starting_value, const char *extra_component) {
  ecs_entity_creation_begin("position", "callback", "tag", "callback-arg", "option-id", "cursor-id", "u32-arg", extra_component);
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(Callback, "callback", callback);
    ecs_entity_creation_setup_component(CallbackArg, "callback-arg", callback_arg);
    ecs_entity_creation_setup_component(Tag, "tag", tag);
    ecs_entity_creation_setup_component(u32, "option-id", id);
    ecs_entity_creation_setup_component(u32, "cursor-id", cursor_id);
    ecs_entity_creation_setup_component(u32, "u32-arg", arg_starting_value);
  ecs_entity_creation_end();
}

void
prefab_menu_cursor(u32 options_amount, u32 id, bool horizontal) {
  ecs_entity_creation_begin("cursor", "cursor-id");
    ecs_entity_creation_setup_component(Cursor, "cursor", ((Cursor) { options_amount, horizontal }));
    ecs_entity_creation_setup_component(u32, "cursor-id", id);
  ecs_entity_creation_end();
}

void
prefab_save_slot(V2f position, u32 id, u32 cursor_id) {
  ecs_entity_creation_begin("position", "character-name", "class", "option-id", "cursor-id");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(u32, "option-id", id);
    ecs_entity_creation_setup_component(u32, "cursor-id", cursor_id);
    ecs_entity_creation_setup_component(CharacterName, "character-name", ((CharacterName) { 0 }));
  ecs_entity_creation_end();
}

void
prefab_character_name_input(V2f position, u32 id, u32 cursor_id, Callback get_character_name) {
  ecs_entity_creation_begin("position", "option-id", "cursor-id", "character-name", "callback");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(u32, "option-id", id);
    ecs_entity_creation_setup_component(u32, "cursor-id", cursor_id);
    ecs_entity_creation_setup_component(Callback, "callback", get_character_name);
    ecs_entity_creation_setup_component(CharacterName, "character-name", ((CharacterName){ 0 }));
  ecs_entity_creation_end();
}

void
prefab_attribute_input(V2f position, AttributeType attribute_type, u32 id, u32 cursor_id, Callback get_attribute) {
  ecs_entity_creation_begin("position", "attribute-type", "option-id", "cursor-id", "attribute-points", "callback");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(AttributeType, "attribute-type", attribute_type);
    ecs_entity_creation_setup_component(u32, "option-id", id);
    ecs_entity_creation_setup_component(u32, "cursor-id", cursor_id);
    ecs_entity_creation_setup_component(i32, "attribute-points", -2);
    ecs_entity_creation_setup_component(Callback, "callback", get_attribute);
  ecs_entity_creation_end();
}

void
prefab_menu_hint(V2f position) {
  ecs_entity_creation_begin("position", "menu-hint", "tag", "color");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(Tag, "tag", "");
  ecs_entity_creation_end();
}

void
prefab_new_character(EntityReference *reference) {
  ecs_entity_creation_begin("character-name", "class", "attributes", "reference-ptr");
    ecs_entity_creation_setup_component(EntityReference *, "reference-ptr", reference);
  ecs_entity_creation_end();
}
