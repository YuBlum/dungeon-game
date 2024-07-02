#include "include/hashtable.h"
#include "include/types.h"
#include "include/window.h"
#include "include/renderer.h"
#include <stdio.h>

i32
main(void) {
  u32 *numbers = hashtable_create(sizeof (u32));
  hashtable_insert(numbers, "hi", 1);
  hashtable_insert(numbers, "hello", 2);
  hashtable_insert(numbers, "test", 3);
  hashtable_insert(numbers, "jad", 4);
  hashtable_insert(numbers, "tur", 5);
  hashtable_insert(numbers, "yuri", 6);
  hashtable_insert(numbers, "what", 7);
  hashtable_insert(numbers, "ola", 8);
  hashtable_insert(numbers, "oiii", 9);
  hashtable_insert(numbers, "??que", 10);
  hashtable_insert(numbers, "uque???", 11);
  hashtable_insert(numbers, "ednaldo", 12);
  hashtable_insert(numbers, "pereira", 13);
  hashtable_insert(numbers, "ednaldo pereira", 14);
  hashtable_insert(numbers, "AAAAAAA", 15);
  hashtable_insert(numbers, "socorro", 16);
  hashtable_insert(numbers, "help please", 17);
  hashtable_insert(numbers, "tf u mean", 18);
  hashtable_insert(numbers, "bitch im baby keem", 19);
  hashtable_insert(numbers, "yeyeyeye", 20);
  hashtable_insert(numbers, "???alo????", 21);
  hashtable_insert(numbers, "sim.", 22);
  hashtable_set(numbers, "oiii", 69);
  printf("numbers['hi'] = %u\n", hashtable_get(numbers, "hi"));
  printf("numbers['hello'] = %u\n", hashtable_get(numbers, "hello"));
  printf("numbers['test'] = %u\n", hashtable_get(numbers, "test"));
  printf("numbers['jad'] = %u\n", hashtable_get(numbers, "jad"));
  printf("numbers['tur'] = %u\n", hashtable_get(numbers, "tur"));
  printf("numbers['yuri'] = %u\n", hashtable_get(numbers, "yuri"));
  printf("numbers['what'] = %u\n", hashtable_get(numbers, "what"));
  printf("numbers['ola'] = %u\n", hashtable_get(numbers, "ola"));
  printf("numbers['oiii'] = %u\n", hashtable_get(numbers, "oiii"));
  printf("numbers['??que'] = %u\n", hashtable_get(numbers, "??que"));
  printf("numbers['uque???\'] = %u\n", hashtable_get(numbers, "uque???"));
  printf("numbers['ednaldo'] = %u\n", hashtable_get(numbers, "ednaldo"));
  printf("numbers['pereira'] = %u\n", hashtable_get(numbers, "pereira"));
  printf("numbers['ednaldo pereira'] = %u\n", hashtable_get(numbers, "ednaldo pereira"));
  printf("numbers['AAAAAAA'] = %u\n", hashtable_get(numbers, "AAAAAAA"));
  printf("numbers['socorro'] = %u\n", hashtable_get(numbers, "socorro"));
  printf("numbers['help please'] = %u\n", hashtable_get(numbers, "help please"));
  printf("numbers['tf u mean'] = %u\n", hashtable_get(numbers, "tf u mean"));
  printf("numbers['bitch im baby keem'] = %u\n", hashtable_get(numbers, "bitch im baby keem"));
  printf("numbers['yeyeyeye'] = %u\n", hashtable_get(numbers, "yeyeyeye"));
  printf("numbers['???alo????\'] = %u\n", hashtable_get(numbers, "???alo????"));
  printf("numbers['sim.'] = %u\n", hashtable_get(numbers, "sim."));
  hashtable_destroy(numbers);
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
