#include "include/components.h"
#include "include/ecs.h"
#include "include/global.h"
#include "include/math.h"
#include "include/tilemap.h"

void
movement_system(void) {
  V2f *position = ecs_get_component_list("position");
  PositionInterpolation *position_interpolation = ecs_get_component_list("position-interpolation");
  f32 *speed = ecs_get_component_list("speed");
  bool *bump = ecs_get_component_list("bump");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (position_interpolation[e].timer >= 1.0f) continue;
    if (!bump[e]) {
      if (position_interpolation[e].timer == 0.0f) {
        tilemap_clear(position_interpolation[e].prv);
        tilemap_set(position_interpolation[e].nxt, e);
      }
      position_interpolation[e].timer += global.dt * speed[e];
      if (position_interpolation[e].timer >= 1.0f) {
        position[e] = position_interpolation[e].nxt;
      } else {
        position[e] = v2f_lerp(position_interpolation[e].prv, position_interpolation[e].nxt, smoothstep(0, 1, position_interpolation[e].timer));
      }
    } else {
      position_interpolation[e].timer += global.dt * speed[e];
      if (position_interpolation[e].timer >= 1.0f) {
        position[e] = position_interpolation[e].prv;
        bump[e] = false;
      } else {
        position[e] = v2f_lerp(position_interpolation[e].prv, position_interpolation[e].nxt, parabola(position_interpolation[e].timer, 0.5f));
      }
    }
  }
}
