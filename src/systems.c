#include "include/ecs.h"
#include "include/input.h"
#include "include/math.h"
#include "include/renderer.h"

static void
system_move(void) {
  V2f *position = ecs_get_component_list("position");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (input_key_pressed(KEY_LEFT))  position[e].x--;
    if (input_key_pressed(KEY_RIGHT)) position[e].x++;
    if (input_key_pressed(KEY_UP))    position[e].y++;
    if (input_key_pressed(KEY_DOWN))  position[e].y--;
  }
}

static void
system_draw_rect(void) {
  V2f *position = ecs_get_component_list("position");
  Color *color = ecs_get_component_list("color");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    renderer_request_quad(position[e], V2S(1), color[e], 0);
  }
}

void
systems_create(void) {
  ecs_system_create(system_move, SYS_UPDATE);
  ecs_system_must_have(system_move, "position", "move-position");

  ecs_system_create(system_draw_rect, SYS_DRAW);
  ecs_system_must_have(system_draw_rect, "position", "color");
}
