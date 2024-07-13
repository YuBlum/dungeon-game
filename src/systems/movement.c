#include "include/components.h"
#include "include/ecs.h"
#include "include/math.h"
#include "include/tilemap.h"
#include "include/global.h"

void
movement_system(void) {
  V2f *position = ecs_get_component_list("position");
  PositionLerp *position_lerp = ecs_get_component_list("position-lerp");
  f32 *speed = ecs_get_component_list("speed");
  bool *bump = ecs_get_component_list("bump");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (position_lerp[e].timer >= 1.0f) continue;
    if (!bump[e]) {
      if (position_lerp[e].timer == 0.0f) {
        tilemap_clear(position_lerp[e].prv);
        tilemap_set(position_lerp[e].nxt, e);
      }
      position_lerp[e].timer += global.all.dt * speed[e];
      if (position_lerp[e].timer >= 1.0f) {
        position[e] = position_lerp[e].nxt;
      } else {
        position[e] = v2f_lerp(position_lerp[e].prv, position_lerp[e].nxt, smoothstep(0, 1, position_lerp[e].timer));
      }
    } else {
      position_lerp[e].timer += global.all.dt * speed[e];
      if (position_lerp[e].timer >= 1.0f) {
        position[e] = position_lerp[e].prv;
        bump[e] = false;
      } else {
        position[e] = v2f_lerp(position_lerp[e].prv, position_lerp[e].nxt, parabola(position_lerp[e].timer, 0.5f));
      }
    }
  }
}
