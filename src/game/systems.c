#include "game/systems.h"
#include "engine/ecs.h"

void
systems_create(void) {
  ecs_system_create(system_set_tile, ON_SCENE_START);
  ecs_system_must_have(system_set_tile, "position");

  ecs_system_create(system_input_direction, ON_UPDATE);
  ecs_system_must_have(system_input_direction, "direction", "input");

  ecs_system_create(system_collision, ON_UPDATE);
  ecs_system_must_have(system_collision, "position", "direction", "position-lerp", "bump");

  ecs_system_create(system_movement, ON_UPDATE);
  ecs_system_must_have(system_movement, "bump");

  ecs_system_create(system_draw_rect, ON_DRAW_GAME);
  ecs_system_must_have(system_draw_rect, "color");

  ecs_system_create(system_draw_character_sheet, ON_DRAW_UI);
  ecs_system_must_have(system_draw_character_sheet, "attributes", "defensive-stats", "character-sheet", "character-name", "class");

  ecs_system_create(system_draw_option, ON_DRAW_SCREEN);
  ecs_system_must_have(system_draw_option, "position", "tag", "option-id");
  ecs_system_must_not_have(system_draw_option, "u32-arg");

  ecs_system_create(system_draw_option_with_u32_arg, ON_DRAW_SCREEN);
  ecs_system_must_have(system_draw_option_with_u32_arg, "position", "tag", "option-id", "u32-arg");

  ecs_system_create(system_cursor_navigation, ON_UPDATE);
  ecs_system_must_have(system_cursor_navigation, "cursor", "cursor-id");

  ecs_system_create(system_select_option, ON_UPDATE);
  ecs_system_must_have(system_select_option, "callback", "callback-arg", "option-id");

  ecs_system_create(system_check_save_slot, ON_SCENE_START);
  ecs_system_must_have(system_check_save_slot, "character-name", "class", "option-id");

  ecs_system_create(system_draw_save_slot, ON_DRAW_SCREEN);
  ecs_system_must_have(system_draw_save_slot, "character-name", "class", "option-id", "position");

  ecs_system_create(system_select_save_slot, ON_UPDATE);
  ecs_system_must_have(system_select_save_slot, "option-id", "cursor-id", "character-name");

  ecs_system_create(system_draw_character_name_input, ON_DRAW_SCREEN);
  ecs_system_must_have(system_draw_character_name_input, "position", "character-name", "option-id");
  
  ecs_system_create(system_global_cursor_update, ON_PRE_UPDATE);
  ecs_system_must_have(system_global_cursor_update, "cursor-id", "cursor");

  ecs_system_create(system_type_character_name_input, ON_UPDATE);
  ecs_system_must_have(system_type_character_name_input, "character-name", "option-id", "cursor-id");

  ecs_system_create(system_total_attribute_points, ON_UPDATE);
  ecs_system_must_have(system_total_attribute_points, "u32-arg", "total-attribute-points");

  ecs_system_create(system_draw_attribute_input, ON_DRAW_SCREEN);
  ecs_system_must_have(system_draw_attribute_input, "position", "attribute-type", "attribute-points", "option-id", "cursor-id");

  ecs_system_create(system_select_attribute_input, ON_UPDATE);
  ecs_system_must_have(system_select_attribute_input, "attribute-type", "attribute-points", "option-id", "cursor-id");

  ecs_system_create(system_menu_hint, ON_UPDATE);
  ecs_system_must_have(system_menu_hint, "menu-hint", "tag", "color");

  ecs_system_create(system_draw_menu_hint, ON_DRAW_SCREEN);
  ecs_system_must_have(system_draw_menu_hint, "position", "menu-hint", "tag", "color");

  ecs_system_create(system_new_character_setup, ON_SCENE_START);
  ecs_system_must_have(system_new_character_setup, "character-name", "class", "attributes", "reference-ptr");

  ecs_system_create(system_submit_character_input, ON_POS_UPDATE);
  ecs_system_must_have(system_submit_character_input, "character-name", "option-id", "cursor-id", "callback");

  ecs_system_create(system_submit_attribute_input, ON_POS_UPDATE);
  ecs_system_must_have(system_submit_attribute_input, "attribute-points", "cursor-id", "callback");

  ecs_system_create(system_delete_save_slot, ON_UPDATE);
  ecs_system_must_have(system_delete_save_slot, "option-id", "cursor-id", "character-name");

  ecs_system_create(system_draw_terminal, ON_DRAW_UI);
  ecs_system_must_have(system_draw_terminal, "terminal");
}
