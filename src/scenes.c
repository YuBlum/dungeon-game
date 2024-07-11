#include "include/core.h"
#include "include/global.h"
#include "include/math.h"
#include "include/scene_manager.h"
#include "include/tilemap.h"
#include "include/prefabs.h"
#include "include/systems.h"
#include "include/scenes.h"


static void
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
  scene_manager_activate_system(main_menu_scene, draw_option_system);
  scene_manager_activate_system(main_menu_scene, hover_on_option_system);
  scene_manager_activate_system(main_menu_scene, select_option_system);

  scene_manager_create_scene(scene_test0);
  scene_manager_activate_system(scene_test0, set_tile_system);
  scene_manager_activate_system(scene_test0, draw_rect_system);
  scene_manager_activate_system(scene_test0, input_direction_system);
  scene_manager_activate_system(scene_test0, collision_system);
  scene_manager_activate_system(scene_test0, movement_system);
  scene_manager_activate_system(scene_test0, draw_char_sheet_system);
}
