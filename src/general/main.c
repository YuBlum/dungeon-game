#include "general/global.h"
#include "engine/serialization.h"
#include "engine/ecs.h"
#include "engine/input.h"
#include "engine/scene_manager.h"
#include "engine/tilemap.h"
#include "general/types.h"
#include "engine/window.h"
#include "engine/renderer.h"
#include "game/components.h"
#include "game/systems.h"

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
    if (global.all.split_screen) {
      renderer_batch_start(RENDER_GAME);
        tilemap_draw();
        ecs_draw_game();
      renderer_batch_end();
      renderer_batch_start(RENDER_UI);
        ecs_draw_ui();
      renderer_batch_end();
    } else {
      renderer_batch_start(RENDER_SCREEN);
        ecs_draw_screen();
      renderer_batch_end();
    }
    renderer_to_window();
    window_frame_end();
  }
  serialization_end();
  return 0;
}
