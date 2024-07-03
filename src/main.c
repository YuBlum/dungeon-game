#include "include/ecs.h"
#include "include/types.h"
#include "include/window.h"
#include "include/renderer.h"

void
update_system(void) {
}

void
draw_system(void) {
  renderer_request_quad(V2F(-0.6, 0), V2F(1, 1), C_YELLOW, 0);
  renderer_request_quad(V2F(+0.6, 0), V2F(1, 1), C_BLUE, 0);
}

i32
main(void) {
  window_create();
  renderer_create();
  ecs_create();
  ecs_system_create(update_system, SYS_UPDATE);
  ecs_system_create(draw_system, SYS_DRAW);

  ecs_component_create(V2f, "position");
  ecs_component_create(V2f, "size");
  Entity e;
  ecs_entity_create(&e, "position", "size");
  *((V2f *)ecs_entity_get_component(e, "position")) = V2F(0,0);
  *((V2f *)ecs_entity_get_component(e, "size")) = V2F(1,1);

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
