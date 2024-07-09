#include "include/components.h"
#include "include/core.h"
#include "include/systems.h"
#include "include/ecs.h"
#include "include/input.h"
#include "include/scene_manager.h"
#include "include/tilemap.h"
#include "include/types.h"
#include "include/window.h"
#include "include/renderer.h"

i32
main(void) {
  window_create();
  renderer_create();
  ecs_create();
  components_create();
  systems_create();
  scene_manager_create();
  while (window_is_running()) {
    window_frame_start();
    scene_manager_update();
    ecs_update();
    input_update();
    renderer_clear(BORDER_COLOR);
    renderer_batch_start(RENDER_GAME);
    tilemap_draw();
    ecs_draw();
    renderer_batch_end(RENDER_GAME);
    renderer_batch_start(RENDER_UI);
    ecs_draw_ui();
    renderer_batch_end(RENDER_UI);
    window_frame_end();
  }
  return 0;
}
