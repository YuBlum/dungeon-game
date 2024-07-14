#include "engine/scene_manager.h"
#include "game/systems.h"
#include "game/scenes.h"

void
scenes_create(void) {
  scene_manager_create_scene(main_menu_scene);
  scene_manager_activate_system(main_menu_scene, cursor_navigation_system);
  scene_manager_activate_system(main_menu_scene, draw_option_system);
  scene_manager_activate_system(main_menu_scene, select_option_system);
  scene_manager_activate_system(main_menu_scene, global_cursor_update_system);

  scene_manager_create_scene(save_slots_menu_scene);
  scene_manager_activate_system(save_slots_menu_scene, cursor_navigation_system);
  scene_manager_activate_system(save_slots_menu_scene, check_save_slot_system);
  scene_manager_activate_system(save_slots_menu_scene, draw_save_slot_system);
  scene_manager_activate_system(save_slots_menu_scene, draw_option_system);
  scene_manager_activate_system(save_slots_menu_scene, select_option_system);
  scene_manager_activate_system(save_slots_menu_scene, select_save_slot_system);
  scene_manager_activate_system(save_slots_menu_scene, global_cursor_update_system);

  scene_manager_create_scene(delete_save_menu_scene);
  scene_manager_activate_system(delete_save_menu_scene, cursor_navigation_system);
  scene_manager_activate_system(delete_save_menu_scene, check_save_slot_system);
  scene_manager_activate_system(delete_save_menu_scene, draw_save_slot_system);
  scene_manager_activate_system(delete_save_menu_scene, draw_option_system);
  scene_manager_activate_system(delete_save_menu_scene, select_option_system);
  scene_manager_activate_system(delete_save_menu_scene, delete_save_slot_system);
  scene_manager_activate_system(delete_save_menu_scene, global_cursor_update_system);

  scene_manager_create_scene(character_creation_scene);
  scene_manager_activate_system(character_creation_scene, cursor_navigation_system);
  scene_manager_activate_system(character_creation_scene, draw_character_name_input_system);
  scene_manager_activate_system(character_creation_scene, draw_option_system);
  scene_manager_activate_system(character_creation_scene, select_option_system);
  scene_manager_activate_system(character_creation_scene, global_cursor_update_system);
  scene_manager_activate_system(character_creation_scene, type_character_name_input_system);
  scene_manager_activate_system(character_creation_scene, draw_option_with_u32_arg_system);
  scene_manager_activate_system(character_creation_scene, total_attribute_points_system);
  scene_manager_activate_system(character_creation_scene, draw_attribute_input_system);
  scene_manager_activate_system(character_creation_scene, select_attribute_input);
  scene_manager_activate_system(character_creation_scene, draw_menu_hint_system);
  scene_manager_activate_system(character_creation_scene, menu_hint_system);
  scene_manager_activate_system(character_creation_scene, new_character_setup_system);
  scene_manager_activate_system(character_creation_scene, submit_character_input_system);
  scene_manager_activate_system(character_creation_scene, submit_attribute_input_system);

  scene_manager_create_scene(overworld_scene);
  scene_manager_activate_system(overworld_scene, set_tile_system);
  scene_manager_activate_system(overworld_scene, draw_rect_system);
  scene_manager_activate_system(overworld_scene, input_direction_system);
  scene_manager_activate_system(overworld_scene, collision_system);
  scene_manager_activate_system(overworld_scene, movement_system);
  scene_manager_activate_system(overworld_scene, draw_character_sheet_system);
}
