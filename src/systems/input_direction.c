#include "include/ecs.h"
#include "include/math.h"
#include "include/input.h"

void
input_direction_system(void) {
  V2f *direction = ecs_get_component_list("direction");
  i32 dir_x = input_key_pressed(KEY_RIGHT) - input_key_pressed(KEY_LEFT);
  i32 dir_y = input_key_pressed(KEY_UP)    - input_key_pressed(KEY_DOWN);
  bool diagonal = dir_x != 0 && dir_y != 0;
  dir_x = (!diagonal) * dir_x;
  dir_y = (!diagonal) * dir_y;
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    direction[e] = V2F(dir_x, dir_y);
  }
}
