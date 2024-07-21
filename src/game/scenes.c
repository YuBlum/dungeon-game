#include "engine/scene_manager.h"
#include "game/scenes.h"

void
scenes_create(void) {
  scene_manager_create_scene("main-menu", scene_main_menu_on_start, scene_main_menu_on_pre_systems, 0, 0);
  scene_manager_activate_system("main-menu", "cursor-navigation");
  scene_manager_activate_system("main-menu", "draw-option-screen");
  scene_manager_activate_system("main-menu", "select-option");

  scene_manager_create_scene("save-slots-menu", scene_save_slots_menu_on_start, scene_save_slots_menu_on_pre_systems, 0, 0);
  scene_manager_activate_system("save-slots-menu", "cursor-navigation");
  scene_manager_activate_system("save-slots-menu", "check-save-slot");
  scene_manager_activate_system("save-slots-menu", "draw-save-slot");
  scene_manager_activate_system("save-slots-menu", "draw-option-screen");
  scene_manager_activate_system("save-slots-menu", "select-option");
  scene_manager_activate_system("save-slots-menu", "select-save-slot");

  scene_manager_create_scene("delete-save-menu", scene_delete_save_menu_on_start, scene_delete_save_menu_on_pre_systems, 0, 0);
  scene_manager_activate_system("delete-save-menu", "cursor-navigation");
  scene_manager_activate_system("delete-save-menu", "check-save-slot");
  scene_manager_activate_system("delete-save-menu", "draw-save-slot");
  scene_manager_activate_system("delete-save-menu", "draw-option-screen");
  scene_manager_activate_system("delete-save-menu", "select-option");
  scene_manager_activate_system("delete-save-menu", "delete-save-slot");

  scene_manager_create_scene("character-creation", scene_character_creation_on_start, scene_character_creation_on_pre_systems, 0, 0);
  scene_manager_activate_system("character-creation", "cursor-navigation");
  scene_manager_activate_system("character-creation", "draw-character-name-input");
  scene_manager_activate_system("character-creation", "draw-option-screen");
  scene_manager_activate_system("character-creation", "select-option");
  scene_manager_activate_system("character-creation", "type-character-name-input");
  scene_manager_activate_system("character-creation", "draw-option-with-u32-arg");
  scene_manager_activate_system("character-creation", "total-attribute-points");
  scene_manager_activate_system("character-creation", "draw-attribute-input");
  scene_manager_activate_system("character-creation", "select-attribute-input");
  scene_manager_activate_system("character-creation", "draw-menu-hint");
  scene_manager_activate_system("character-creation", "menu-hint");
  scene_manager_activate_system("character-creation", "submit-character-input");
  scene_manager_activate_system("character-creation", "submit-attribute-input");

  scene_manager_create_scene("overworld", scene_overworld_on_start, scene_overworld_on_pre_systems, 0, scene_overworld_on_draw);
  scene_manager_activate_system("overworld", "set-tile");
  scene_manager_activate_system("overworld", "draw-rect");
  scene_manager_activate_system("overworld", "input-direction");
  scene_manager_activate_system("overworld", "collision");
  scene_manager_activate_system("overworld", "movement");
  scene_manager_activate_system("overworld", "draw-character-sheet");
  scene_manager_activate_system("overworld", "draw-terminal");
  scene_manager_activate_system("overworld", "pause");
  scene_manager_activate_system("overworld", "cursor-navigation");
  scene_manager_activate_system("overworld", "draw-option-ui");
  scene_manager_activate_system("overworld", "select-option");
  scene_manager_activate_system("overworld", "activate-game-option");
  scene_manager_activate_system("overworld", "draw-carrying-weight");
  scene_manager_activate_system("overworld", "draw-item");
  scene_manager_activate_system("overworld", "remove-item");
  scene_manager_activate_system("overworld", "items-offset");
  scene_manager_activate_system("overworld", "select-item");
  scene_manager_activate_system("overworld", "update-item-id");
  scene_manager_activate_system("overworld", "item-melee-description");
  scene_manager_activate_system("overworld", "item-ranged-description");
  scene_manager_activate_system("overworld", "item-staff-description");
  scene_manager_activate_system("overworld", "item-defensive-description");
  scene_manager_activate_system("overworld", "item-potion-description");
}
