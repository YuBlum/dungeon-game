#include "include/core.h"
#include "include/types.h"
#include "include/window.h"
#include "include/renderer.h"

#include "include/list.h"

i32
main(void) {
  u32 *numbers = list_create(sizeof (u32));
  list_push(numbers, 0);
  list_push(numbers, 1);
  list_push(numbers, 2);
  list_push(numbers, 3);
  list_push(numbers, 4);
  list_push(numbers, 5);
  list_push(numbers, 6);
  list_push(numbers, 7);
  for (u32 i = 0; i < list_size(numbers); i++) { INFO("numbers[%u] = %u", i, numbers[i]); } INFO();
  list_pop(numbers);
  list_pop(numbers);
  for (u32 i = 0; i < list_size(numbers); i++) { INFO("numbers[%u] = %u", i, numbers[i]); } INFO();
  list_insert(numbers, 2, 8);
  list_insert(numbers, 2, 9);
  for (u32 i = 0; i < list_size(numbers); i++) { INFO("numbers[%u] = %u", i, numbers[i]); } INFO();
  list_remove(numbers, 5);
  list_remove(numbers, 0);
  for (u32 i = 0; i < list_size(numbers); i++) { INFO("numbers[%u] = %u", i, numbers[i]); } INFO();
  list_destroy(numbers);

  return 0;
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
