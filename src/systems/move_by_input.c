#include "include/components.h"
#include "include/ecs.h"
#include "include/math.h"
#include "include/tilemap.h"
#include "include/input.h"

void
move_by_input_system(void) {
  V2f *position = ecs_get_component_list("position");
  PositionInterpolation *position_interpolation = ecs_get_component_list("position-interpolation");
  bool *bump = ecs_get_component_list("bump");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (position_interpolation[e].timer < 1.0f) continue;
    V2f dir = {
      input_key_pressed(KEY_RIGHT) - input_key_pressed(KEY_LEFT),
      input_key_pressed(KEY_UP)    - input_key_pressed(KEY_DOWN)
    };
    if ((dir.x != 0 || dir.y != 0) && (dir.x == 0 || dir.y == 0)) {
      position_interpolation[e].nxt = v2f_add(position[e], dir);
      EntityReference collided_entity = tilemap_get(position_interpolation[e].nxt);
      if (!collided_entity) {
        position_interpolation[e].prv = position[e];
        position_interpolation[e].timer = 0.0f;
      } else {
        bump[e] = true;
        position_interpolation[e].nxt = v2f_add(position[e], v2f_muls(dir, 0.2f));
        position_interpolation[e].prv = position[e];
        position_interpolation[e].timer = 0.0f;
      }
    }
  }
}
