#include "include/core.h"
#include "include/math.h"
#include "include/scene_manager.h"
#include "include/tilemap.h"
#include "include/prefabs.h"
#include "include/systems.h"

static void
scene_test0(void) {
  tilemap_setup(GAME_W, GAME_H);
  prefab_solid(V2F(2, 2));
  prefab_solid(V2F(1, 1));
  prefab_solid(V2F(2, 1));
  prefab_solid(V2F(1, 2));
  prefab_player(V2FS(0));
}

void
scenes_create(void) {
  scene_manager_create_scene(scene_test0);
  scene_manager_activate_system(scene_test0, set_tile_system);
  scene_manager_activate_system(scene_test0, draw_rect_system);
  scene_manager_activate_system(scene_test0, input_direction_system);
  scene_manager_activate_system(scene_test0, collision_system);
  scene_manager_activate_system(scene_test0, movement_system);
  scene_manager_activate_system(scene_test0, draw_char_sheet_system);
}
