#include "include/components.h"
#include "include/systems.h"
#include "include/scenes.h"
#include "include/ecs.h"
#include "include/input.h"
#include "include/scene_manager.h"
#include "include/types.h"
#include "include/window.h"
#include "include/renderer.h"

i32
main(void) {
  window_create();
  renderer_create();
  ecs_create();
  scene_manager_create();
  components_create();
  systems_create();
  scenes_create();
  while (window_is_running()) {
    window_frame_start();
    scene_manager_update();
    ecs_update();
    input_update();
    renderer_batch_start();
    ecs_draw();
    renderer_batch_end();
    window_frame_end();
  }
  return 0;
}
