#include "include/core.h"
#include "include/ecs.h"
#include "include/math.h"
#include "include/types.h"
#include "include/window.h"
#include "include/renderer.h"

void
move_system(void) {
  V2f *position = ecs_get_component_list("position");
  V2f *velocity = ecs_get_component_list("velocity");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    position[e] = v2_add(position[e], velocity[e]);
    if (position[e].x > -.5) ecs_entity_remove_component(e, "velocity");
  }
}

void
draw_system(void) {
  V2f   *position = ecs_get_component_list("position");
  V2f   *size     = ecs_get_component_list("size");
  Color *color    = ecs_get_component_list("color");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    renderer_request_quad(position[e], size[e], color[e], 0);
  }
}

void
static_rect_create(V2f position, V2f size, Color color) {
  ecs_entity_creation_begin("position", "size", "color");
    ecs_entity_creation_setup_component(Color, "color",    color);
    ecs_entity_creation_setup_component(V2f,   "size",     size);
    ecs_entity_creation_setup_component(V2f,   "position", position);
  ecs_entity_creation_end();
}

void
movable_rect_create(V2f position, V2f size, V2f velocity, Color color) {
  ecs_entity_creation_begin("position", "velocity", "size", "color");
    ecs_entity_creation_setup_component(Color, "color",    color);
    ecs_entity_creation_setup_component(V2f,   "size",     size);
    ecs_entity_creation_setup_component(V2f,   "position", position);
    ecs_entity_creation_setup_component(V2f,   "velocity", velocity);
  ecs_entity_creation_end();
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

  movable_rect_create(V2F(-5.0f, +4.0f), V2S(1.0f), V2F(0.01f, 0.00f), C_YELLOW);
  movable_rect_create(V2F(-7.0f, +3.0f), V2S(0.6f), V2F(0.01f, 0.00f), C_WHITE);
  movable_rect_create(V2F(-4.0f, +2.0f), V2S(0.4f), V2F(0.01f, 0.00f), C_BLUE);
  movable_rect_create(V2F(-3.0f, -1.0f), V2S(0.3f), V2F(0.01f, 0.00f), C_GREEN);
  movable_rect_create(V2F(-5.5f, -2.0f), V2S(1.2f), V2F(0.01f, 0.00f), C_BLACK);
  movable_rect_create(V2F(-4.5f, -3.0f), V2S(0.4f), V2F(0.01f, 0.00f), C_MAGENTA);
  movable_rect_create(V2F(-6.0f, -4.0f), V2S(1.0f), V2F(0.01f, 0.00f), C_YELLOW);
  /*
  
  static_rect_create(V2F(+5.0f, +0.0f), V2F(1.0f, 1.0f), C_YELLOW);
  static_rect_create(V2F(+7.0f, -4.0f), V2F(5.0f, 1.0f), C_WHITE);
  static_rect_create(V2F(-6.0f, +4.0f), V2F(2.0f, 1.5f), C_BLUE);
  static_rect_create(V2F(-2.0f, -2.0f), V2F(0.25f, 0.25f), C_GREEN);

  movable_rect_create(V2F(+5.0f, +0.0f), V2F(0.25f, 0.25f), V2F(0.05f, 0.00f), C_YELLOW);
  movable_rect_create(V2F(+5.0f, -4.0f), V2F(2.0f, 1.5f),   V2F(0.05f, 0.05f), C_WHITE);
  movable_rect_create(V2F(-6.0f, +4.0f), V2F(1.0f, 1.0f),   V2F(0.00f, -0.05f), C_BLUE);
  movable_rect_create(V2F(-2.0f, -2.0f), V2F(5.0f, 1.0f),   V2F(-0.05f, 0.00f), C_GREEN);
  */

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
