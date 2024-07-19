#include "engine/scene_manager.h"
#include "game/scenes.h"

void
scenes_create(void) {
  scene_manager_create_scene(scene_main_menu);
  scene_manager_activate_system(scene_main_menu, "cursor-navigation");
  scene_manager_activate_system(scene_main_menu, "draw-option-screen");
  scene_manager_activate_system(scene_main_menu, "select-option");
  scene_manager_activate_system(scene_main_menu, "global-cursor-update");

  scene_manager_create_scene(scene_save_slots_menu);
  scene_manager_activate_system(scene_save_slots_menu, "cursor-navigation");
  scene_manager_activate_system(scene_save_slots_menu, "check-save-slot");
  scene_manager_activate_system(scene_save_slots_menu, "draw-save-slot");
  scene_manager_activate_system(scene_save_slots_menu, "draw-option-screen");
  scene_manager_activate_system(scene_save_slots_menu, "select-option");
  scene_manager_activate_system(scene_save_slots_menu, "select-save-slot");
  scene_manager_activate_system(scene_save_slots_menu, "global-cursor-update");

  scene_manager_create_scene(scene_delete_save_menu);
  scene_manager_activate_system(scene_delete_save_menu, "cursor-navigation");
  scene_manager_activate_system(scene_delete_save_menu, "check-save-slot");
  scene_manager_activate_system(scene_delete_save_menu, "draw-save-slot");
  scene_manager_activate_system(scene_delete_save_menu, "draw-option-screen");
  scene_manager_activate_system(scene_delete_save_menu, "select-option");
  scene_manager_activate_system(scene_delete_save_menu, "delete-save-slot");
  scene_manager_activate_system(scene_delete_save_menu, "global-cursor-update");

  scene_manager_create_scene(scene_character_creation);
  scene_manager_activate_system(scene_character_creation, "cursor-navigation");
  scene_manager_activate_system(scene_character_creation, "draw-character-name-input");
  scene_manager_activate_system(scene_character_creation, "draw-option-screen");
  scene_manager_activate_system(scene_character_creation, "select-option");
  scene_manager_activate_system(scene_character_creation, "global-cursor-update");
  scene_manager_activate_system(scene_character_creation, "type-character-name-input");
  scene_manager_activate_system(scene_character_creation, "draw-option-with-u32-arg");
  scene_manager_activate_system(scene_character_creation, "total-attribute-points");
  scene_manager_activate_system(scene_character_creation, "draw-attribute-input");
  scene_manager_activate_system(scene_character_creation, "select-attribute-input");
  scene_manager_activate_system(scene_character_creation, "draw-menu-hint");
  scene_manager_activate_system(scene_character_creation, "menu-hint");
  scene_manager_activate_system(scene_character_creation, "new-character-setup");
  scene_manager_activate_system(scene_character_creation, "submit-character-input");
  scene_manager_activate_system(scene_character_creation, "submit-attribute-input");

  scene_manager_create_scene(scene_overworld);
  scene_manager_activate_system(scene_overworld, "set-tile");
  scene_manager_activate_system(scene_overworld, "draw-rect");
  scene_manager_activate_system(scene_overworld, "input-direction");
  scene_manager_activate_system(scene_overworld, "collision");
  scene_manager_activate_system(scene_overworld, "movement");
  scene_manager_activate_system(scene_overworld, "draw-character-sheet");
  scene_manager_activate_system(scene_overworld, "draw-terminal");
  scene_manager_activate_system(scene_overworld, "pause");
  scene_manager_activate_system(scene_overworld, "cursor-navigation");
  scene_manager_activate_system(scene_overworld, "draw-option-ui");
  scene_manager_activate_system(scene_overworld, "select-option");
  scene_manager_activate_system(scene_overworld, "global-cursor-update");
  scene_manager_activate_system(scene_overworld, "activate-game-option");
  scene_manager_activate_system(scene_overworld, "in-game-menu-title");
  scene_manager_activate_system(scene_overworld, "draw-carrying-weight");
  scene_manager_activate_system(scene_overworld, "inventory-header");
  scene_manager_activate_system(scene_overworld, "draw-item");
  scene_manager_activate_system(scene_overworld, "update-items-amount");
  scene_manager_activate_system(scene_overworld, "items-offset");
}
