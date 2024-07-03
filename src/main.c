#include "include/ecs.h"
#include "include/math.h"
#include "include/types.h"
#include "include/window.h"
#include "include/renderer.h"

void
move_system(void) {
  V2f *position = ecs_get_component_list("position");
  V2f *velocity = ecs_get_component_list("velocity");
  for (EntityID id = 0; id < ecs_entities_amount(); id++) {
    position[id] = v2_add(position[id], velocity[id]);
  }
}

void
draw_system(void) {
  V2f   *position = ecs_get_component_list("position");
  V2f   *size     = ecs_get_component_list("size");
  Color *color    = ecs_get_component_list("color");
  for (EntityID id = 0; id < ecs_entities_amount(); id++) {
    renderer_request_quad(position[id], size[id], color[id], 0);
  }
}

i32
main(void) {
  window_create();
  renderer_create();
  ecs_create();

  ecs_component_create(V2f, "position");
  ecs_component_create(V2f, "size");
  ecs_component_create(V2f, "velocity");
  ecs_component_create(Color, "color");

  ecs_system_create(move_system, SYS_UPDATE, "position", "velocity");
  ecs_system_create(draw_system, SYS_DRAW, "position", "size", "color");

  Entity entity;

  ecs_entity_create(&entity, "position", "size", "color");
  *((V2f *)ecs_entity_get_component(entity, "position")) = V2F(0,0);
  *((V2f *)ecs_entity_get_component(entity, "size")) = V2F(1,1);
  *((Color *)ecs_entity_get_component(entity, "color")) = C_YELLOW;

  ecs_entity_create(&entity, "position", "velocity", "size", "color");
  *((V2f *)ecs_entity_get_component(entity, "position")) = V2F(0,0);
  *((V2f *)ecs_entity_get_component(entity, "velocity")) = V2F(0.05f,0);
  *((V2f *)ecs_entity_get_component(entity, "size")) = V2F(1,1);
  *((Color *)ecs_entity_get_component(entity, "color")) = C_GREEN;

  while (window_is_running()) {
    window_frame_start();
    ecs_update();
    renderer_batch_start();
    ecs_draw();
    renderer_batch_end();
    window_frame_end();
  }
  return 0;
}
