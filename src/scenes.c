#include "include/core.h"
#include "include/global.h"
#include "include/math.h"
#include "include/scene_manager.h"
#include "include/tilemap.h"
#include "include/prefabs.h"
#include "include/systems.h"
#include "include/scenes.h"

void
scene_test0(void) {
  tilemap_setup(GAME_W, GAME_H);
  prefab_solid(V2F(2, 2));
  prefab_solid(V2F(1, 1));
  prefab_solid(V2F(2, 1));
  prefab_solid(V2F(1, 2));
  prefab_player(V2FS(0));
  global.split_screen = true;
}

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

  scene_manager_create_scene(scene_test0);
  scene_manager_activate_system(scene_test0, set_tile_system);
  scene_manager_activate_system(scene_test0, draw_rect_system);
  scene_manager_activate_system(scene_test0, input_direction_system);
  scene_manager_activate_system(scene_test0, collision_system);
  scene_manager_activate_system(scene_test0, movement_system);
  scene_manager_activate_system(scene_test0, draw_character_sheet_system);
}
