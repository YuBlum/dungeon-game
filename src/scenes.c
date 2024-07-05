#include "include/core.h"
#include "include/ecs.h"
#include "include/math.h"
#include "include/scene_manager.h"
#include "include/tilemap.h"

static void
scene_test0(void) {
  ecs_system_activate(system_draw_rect);
  ecs_system_activate(system_apply_movement);
  ecs_system_activate(system_move_by_input);

  tilemap_setup(GAME_W, GAME_H);
  tilemap_set(V2F(2, 2), TILE_SOLID, true);
  tilemap_set(V2F(1, 1), TILE_SOLID, true);
  tilemap_set(V2F(2, 1), TILE_SOLID, true);
  tilemap_set(V2F(1, 2), TILE_SOLID, true);
  tilemap_set(V2FS(0), TILE_PLAYER, true);
}

void
scenes_create(void) {
  scene_manager_create_scene(scene_test0);
}
