#include "include/ecs.h"
#include "include/math.h"
#include "include/renderer.h"
#include "include/scene_manager.h"
#include "include/prefabs.h"

static void
scene_test0(void) {
  ecs_system_activate(system_draw_rect);
  ecs_system_activate(system_apply_movement);
  ecs_system_activate(system_move_by_input);

  prefab_player(V2F(-0.5f, 0.5f));
}

void
scenes_create(void) {
  scene_manager_create_scene(scene_test0);
}
