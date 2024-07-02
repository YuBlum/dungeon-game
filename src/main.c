#include "include/types.h"
#include "include/window.h"
#include "include/renderer.h"

i32
main(void) {
  window_create();
  renderer_create();
  while (window_is_running()) {
    window_frame_start();
    renderer_batch_start();
    renderer_request_quad(V2F(-0.6, 0), V2F(1, 1), C_YELLOW, 0);
    renderer_request_quad(V2F(+0.6, 0), V2F(1, 1), C_BLUE, 0);
    renderer_batch_end();
    window_frame_end();
  }
  return 0;
}
