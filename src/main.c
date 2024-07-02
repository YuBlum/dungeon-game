#include "include/core.h"
#include "include/window.h"
#include "include/renderer.h"

i32
main(void) {
  window_create();
  renderer_create();
  while (window_is_running()) {
    window_frame_start();
    renderer_update();
    window_frame_end();
  }
  return 0;
}
