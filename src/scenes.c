#include "include/ecs.h"
#include "include/math.h"
#include "include/renderer.h"
#include "include/scene_manager.h"
#include "include/prefabs.h"

static void
scene_test0(void) {
  ecs_system_activate(system_draw);
  ecs_system_activate(system_scene_changer);

  prefab_rect(V2S(0), V2S(1), C_YELLOW);

  ecs_entity_creation_begin("control");
  ecs_entity_creation_end();
}

static void
scene_test1(void) {
  ecs_system_activate(system_draw);
  ecs_system_activate(system_scene_changer);

  prefab_rect(V2S(0), V2S(1), C_BLUE);

  ecs_entity_creation_begin("control");
  ecs_entity_creation_end();
}

void
scenes_create(void) {
  scene_manager_create_scene(scene_test0);
  scene_manager_create_scene(scene_test1);
}
