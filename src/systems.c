#include "include/systems.h"
#include "include/ecs.h"

void
systems_create(void) {
  ecs_system_create(set_tile_system, SYS_SCENE_START);
  ecs_system_must_have(set_tile_system, "position");

  ecs_system_create(move_by_input_system, SYS_UPDATE);
  ecs_system_must_have(move_by_input_system, "bump");

  ecs_system_create(movement_system, SYS_UPDATE);
  ecs_system_must_have(movement_system, "bump");

  ecs_system_create(draw_rect_system, SYS_DRAW);
  ecs_system_must_have(draw_rect_system, "color");
}
