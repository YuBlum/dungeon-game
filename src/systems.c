#include "include/core.h"
#include "include/ecs.h"
#include "include/input.h"
#include "include/math.h"
#include "include/renderer.h"
#include "include/scene_manager.h"

static void
system_scene_changer(void) {
  if (input_key_pressed(KEY_A)) {
    if (scene_manager_is_current_scene(scene_test0)) {
      scene_manager_goto_next();
    } else {
      scene_manager_goto_prev();
    }
  }
}

static void
system_draw(void) {
  V2f *position = ecs_get_component_list("position");
  V2f *size = ecs_get_component_list("size");
  Color *color = ecs_get_component_list("color");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    renderer_request_quad(position[e], size[e], color[e], 0);
  }
}

void
systems_create(void) {
  ecs_system_create(system_draw, SYS_DRAW);
  ecs_system_must_have(system_draw, "position", "size", "color");

  ecs_system_create(system_scene_changer, SYS_UPDATE);
  ecs_system_must_have(system_scene_changer, "control");
}
