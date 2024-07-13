#include "include/systems.h"
#include "include/ecs.h"

void
systems_create(void) {
  ecs_system_create(set_tile_system, ON_SCENE_START);
  ecs_system_must_have(set_tile_system, "position");

  ecs_system_create(input_direction_system, ON_UPDATE);
  ecs_system_must_have(input_direction_system, "direction", "input");

  ecs_system_create(collision_system, ON_UPDATE);
  ecs_system_must_have(collision_system, "position", "direction", "position-lerp", "bump");

  ecs_system_create(movement_system, ON_UPDATE);
  ecs_system_must_have(movement_system, "bump");

  ecs_system_create(draw_rect_system, ON_DRAW_GAME);
  ecs_system_must_have(draw_rect_system, "color");

  ecs_system_create(draw_character_sheet_system, ON_DRAW_UI);
  ecs_system_must_have(draw_character_sheet_system, "attributes", "defensive-stats", "character-sheet", "character-name", "class");

  ecs_system_create(draw_option_system, ON_DRAW_SCREEN);
  ecs_system_must_have(draw_option_system, "position", "tag", "option-id");
  ecs_system_must_not_have(draw_option_system, "u32-arg");

  ecs_system_create(draw_option_with_u32_arg_system, ON_DRAW_SCREEN);
  ecs_system_must_have(draw_option_with_u32_arg_system, "position", "tag", "option-id", "u32-arg");

  ecs_system_create(cursor_navigation_system, ON_UPDATE);
  ecs_system_must_have(cursor_navigation_system, "cursor", "cursor-id");

  ecs_system_create(select_option_system, ON_UPDATE);
  ecs_system_must_have(select_option_system, "callback", "callback-arg", "option-id");

  ecs_system_create(check_save_slot_system, ON_SCENE_START);
  ecs_system_must_have(check_save_slot_system, "character-name", "class", "option-id");

  ecs_system_create(draw_save_slot_system, ON_DRAW_SCREEN);
  ecs_system_must_have(draw_save_slot_system, "character-name", "class", "option-id", "position");

  ecs_system_create(select_save_slot_system, ON_UPDATE);
  ecs_system_must_have(select_save_slot_system, "option-id", "character-name");

  ecs_system_create(draw_character_name_input_system, ON_DRAW_SCREEN);
  ecs_system_must_have(draw_character_name_input_system, "position", "character-name", "option-id");
  
  ecs_system_create(global_cursor_update_system, ON_PRE_UPDATE);
  ecs_system_must_have(global_cursor_update_system, "cursor-id", "cursor");

  ecs_system_create(type_character_name_input_system, ON_UPDATE);
  ecs_system_must_have(type_character_name_input_system, "character-name", "option-id", "cursor-id");

  ecs_system_create(total_attribute_points_system, ON_UPDATE);
  ecs_system_must_have(total_attribute_points_system, "u32-arg", "total-attribute-points");

  ecs_system_create(draw_attribute_input_system, ON_DRAW_SCREEN);
  ecs_system_must_have(draw_attribute_input_system, "position", "attribute-type", "attribute-points", "option-id", "cursor-id");

  ecs_system_create(select_attribute_input, ON_UPDATE);
  ecs_system_must_have(select_attribute_input, "attribute-type", "attribute-points", "option-id", "cursor-id");

  ecs_system_create(menu_hint_system, ON_UPDATE);
  ecs_system_must_have(menu_hint_system, "menu-hint", "tag", "color");

  ecs_system_create(draw_menu_hint_system, ON_DRAW_SCREEN);
  ecs_system_must_have(draw_menu_hint_system, "position", "menu-hint", "tag", "color");

  ecs_system_create(new_character_setup_system, ON_SCENE_START);
  ecs_system_must_have(new_character_setup_system, "character-name", "class", "attributes", "reference-ptr");

  ecs_system_create(submit_character_input_system, ON_POS_UPDATE);
  ecs_system_must_have(submit_character_input_system, "character-name", "option-id", "cursor-id", "callback");

  ecs_system_create(submit_attribute_input_system, ON_POS_UPDATE);
  ecs_system_must_have(submit_attribute_input_system, "attribute-points", "cursor-id", "callback");
}
