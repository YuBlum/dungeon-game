#include "game/systems.h"
#include "engine/ecs.h"

void
systems_create(void) {
  ecs_system_create("set-tile", system_set_tile, ON_SCENE_START);
  ecs_system_must_have("set-tile", "tile", "position");

  ecs_system_create("input-direction", system_input_direction, ON_UPDATE);
  ecs_system_must_have("input-direction", "direction", "input");

  ecs_system_create("collision", system_collision, ON_UPDATE);
  ecs_system_must_have("collision", "position", "direction", "position-lerp", "bump");

  ecs_system_create("movement", system_movement, ON_UPDATE);
  ecs_system_must_have("movement", "bump");

  ecs_system_create("draw-rect", system_draw_rect, ON_DRAW_GAME);
  ecs_system_must_have("draw-rect", "tile", "position", "color");

  ecs_system_create("draw-character-sheet", system_draw_character_sheet, ON_DRAW_UI);
  ecs_system_must_have("draw-character-sheet", "attributes", "defensive-stats", "character-sheet", "character-name", "class");

  ecs_system_create("draw-option-screen", system_draw_option, ON_DRAW_SCREEN);
  ecs_system_must_have("draw-option-screen", "position", "tag", "option-id");
  ecs_system_must_not_have("draw-option-screen", "u32-arg");

  ecs_system_create("draw-option-ui", system_draw_option, ON_DRAW_UI);
  ecs_system_must_have("draw-option-ui", "position", "tag", "option-id");
  ecs_system_must_not_have("draw-option-ui", "u32-arg");

  ecs_system_create("draw-option-with-u32-arg", system_draw_option_with_u32_arg, ON_DRAW_SCREEN);
  ecs_system_must_have("draw-option-with-u32-arg", "position", "tag", "option-id", "u32-arg");

  ecs_system_create("cursor-navigation", system_cursor_navigation, ON_UPDATE);
  ecs_system_must_have("cursor-navigation", "cursor", "cursor-id");

  ecs_system_create("select-option", system_select_option, ON_UPDATE);
  ecs_system_must_have("select-option", "callback", "callback-arg", "option-id");

  ecs_system_create("check-save-slot", system_check_save_slot, ON_SCENE_START);
  ecs_system_must_have("check-save-slot", "character-name", "class", "option-id");

  ecs_system_create("draw-save-slot", system_draw_save_slot, ON_DRAW_SCREEN);
  ecs_system_must_have("draw-save-slot", "character-name", "class", "option-id", "position");

  ecs_system_create("select-save-slot", system_select_save_slot, ON_UPDATE);
  ecs_system_must_have("select-save-slot", "option-id", "cursor-id", "character-name");

  ecs_system_create("draw-character-name-input", system_draw_character_name_input, ON_DRAW_SCREEN);
  ecs_system_must_have("draw-character-name-input", "position", "character-name", "option-id");

  ecs_system_create("type-character-name-input", system_type_character_name_input, ON_UPDATE);
  ecs_system_must_have("type-character-name-input", "character-name", "option-id", "cursor-id");

  ecs_system_create("total-attribute-points", system_total_attribute_points, ON_UPDATE);
  ecs_system_must_have("total-attribute-points", "u32-arg", "total-attribute-points");

  ecs_system_create("draw-attribute-input", system_draw_attribute_input, ON_DRAW_SCREEN);
  ecs_system_must_have("draw-attribute-input", "position", "attribute-type", "attribute-points", "option-id", "cursor-id");

  ecs_system_create("select-attribute-input", system_select_attribute_input, ON_UPDATE);
  ecs_system_must_have("select-attribute-input", "attribute-type", "attribute-points", "option-id", "cursor-id");

  ecs_system_create("menu-hint", system_menu_hint, ON_UPDATE);
  ecs_system_must_have("menu-hint", "menu-hint", "tag", "color");

  ecs_system_create("draw-menu-hint", system_draw_menu_hint, ON_DRAW_SCREEN);
  ecs_system_must_have("draw-menu-hint", "position", "menu-hint", "tag", "color");

  ecs_system_create("submit-character-input", system_submit_character_input, ON_POS_UPDATE);
  ecs_system_must_have("submit-character-input", "character-name", "option-id", "cursor-id", "callback");

  ecs_system_create("submit-attribute-input", system_submit_attribute_input, ON_POS_UPDATE);
  ecs_system_must_have("submit-attribute-input", "attribute-points", "cursor-id", "callback");

  ecs_system_create("delete-save-slot", system_delete_save_slot, ON_UPDATE);
  ecs_system_must_have("delete-save-slot", "option-id", "cursor-id", "character-name");

  ecs_system_create("draw-terminal", system_draw_terminal, ON_DRAW_UI);
  ecs_system_must_have("draw-terminal", "terminal");

  ecs_system_create("pause", system_pause, ON_UPDATE);
  ecs_system_must_have("pause", "pause");

  ecs_system_create("activate-game-option", system_activate_game_option, ON_PRE_UPDATE);
  ecs_system_must_have("activate-game-option", "active", "in-game-menu-type", "option-id");

  ecs_system_create("draw-carrying-weight", system_draw_carrying_weight, ON_DRAW_UI);
  ecs_system_must_have("draw-carrying-weight", "character-sheet");

  ecs_system_create("draw-item", system_draw_item, ON_DRAW_UI);
  ecs_system_must_have("draw-item", "item-info");

  ecs_system_create("remove-item", system_remove_item, ON_DESTROY);
  ecs_system_must_have("remove-item", "item-info");
  
  ecs_system_create("items-offset", system_items_offset, ON_UPDATE);
  ecs_system_must_have("items-offset", "cursor-id");

  ecs_system_create("select-item", system_select_item, ON_UPDATE);
  ecs_system_must_have("select-item", "item-info");

  ecs_system_create("update-item-id", system_update_item_id, ON_POS_UPDATE);
  ecs_system_must_have("update-item-id", "item-info");

  ecs_system_create("item-melee-description", system_item_melee_description, ON_DRAW_UI);
  ecs_system_must_have("item-melee-description", "item-info", "dice-test", "item-melee", "attribute-threshold", "critical-hit");

  ecs_system_create("item-ranged-description", system_item_ranged_description, ON_DRAW_UI);
  ecs_system_must_have("item-ranged-description", "item-info", "dice-test", "item-ranged", "attribute-threshold", "critical-hit", "ammo-type");

  ecs_system_create("item-staff-description", system_item_staff_description, ON_DRAW_UI);
  ecs_system_must_have("item-staff-description", "item-info", "item-staff", "attribute-threshold", "staff");

  ecs_system_create("item-defensive-description", system_item_defensive_description, ON_DRAW_UI);
  ecs_system_must_have("item-defensive-description", "item-info", "item-defensive", "attribute-threshold", "defensive-item");

  ecs_system_create("item-potion-description", system_item_potion_description, ON_DRAW_UI);
  ecs_system_must_have("item-potion-description", "item-info", "item-potion", "dice-test", "potion-type");
}
