#include "engine/scene_manager.h"
#include "game/systems.h"
#include "game/scenes.h"

void
scenes_create(void) {
  scene_manager_create_scene(scene_main_menu);
  scene_manager_activate_system(scene_main_menu, system_cursor_navigation);
  scene_manager_activate_system(scene_main_menu, system_draw_option);
  scene_manager_activate_system(scene_main_menu, system_select_option);
  scene_manager_activate_system(scene_main_menu, system_global_cursor_update);

  scene_manager_create_scene(scene_save_slots_menu);
  scene_manager_activate_system(scene_save_slots_menu, system_cursor_navigation);
  scene_manager_activate_system(scene_save_slots_menu, system_check_save_slot);
  scene_manager_activate_system(scene_save_slots_menu, system_draw_save_slot);
  scene_manager_activate_system(scene_save_slots_menu, system_draw_option);
  scene_manager_activate_system(scene_save_slots_menu, system_select_option);
  scene_manager_activate_system(scene_save_slots_menu, system_select_save_slot);
  scene_manager_activate_system(scene_save_slots_menu, system_global_cursor_update);

  scene_manager_create_scene(scene_delete_save_menu);
  scene_manager_activate_system(scene_delete_save_menu, system_cursor_navigation);
  scene_manager_activate_system(scene_delete_save_menu, system_check_save_slot);
  scene_manager_activate_system(scene_delete_save_menu, system_draw_save_slot);
  scene_manager_activate_system(scene_delete_save_menu, system_draw_option);
  scene_manager_activate_system(scene_delete_save_menu, system_select_option);
  scene_manager_activate_system(scene_delete_save_menu, system_delete_save_slot);
  scene_manager_activate_system(scene_delete_save_menu, system_global_cursor_update);

  scene_manager_create_scene(scene_character_creation);
  scene_manager_activate_system(scene_character_creation, system_cursor_navigation);
  scene_manager_activate_system(scene_character_creation, system_draw_character_name_input);
  scene_manager_activate_system(scene_character_creation, system_draw_option);
  scene_manager_activate_system(scene_character_creation, system_select_option);
  scene_manager_activate_system(scene_character_creation, system_global_cursor_update);
  scene_manager_activate_system(scene_character_creation, system_type_character_name_input);
  scene_manager_activate_system(scene_character_creation, system_draw_option_with_u32_arg);
  scene_manager_activate_system(scene_character_creation, system_total_attribute_points);
  scene_manager_activate_system(scene_character_creation, system_draw_attribute_input);
  scene_manager_activate_system(scene_character_creation, system_select_attribute_input);
  scene_manager_activate_system(scene_character_creation, system_draw_menu_hint);
  scene_manager_activate_system(scene_character_creation, system_menu_hint);
  scene_manager_activate_system(scene_character_creation, system_new_character_setup);
  scene_manager_activate_system(scene_character_creation, system_submit_character_input);
  scene_manager_activate_system(scene_character_creation, system_submit_attribute_input);

  scene_manager_create_scene(scene_overworld);
  scene_manager_activate_system(scene_overworld, system_set_tile);
  scene_manager_activate_system(scene_overworld, system_draw_rect);
  scene_manager_activate_system(scene_overworld, system_input_direction);
  scene_manager_activate_system(scene_overworld, system_collision);
  scene_manager_activate_system(scene_overworld, system_movement);
  scene_manager_activate_system(scene_overworld, system_draw_character_sheet);
  scene_manager_activate_system(scene_overworld, system_draw_terminal);
}
