#include "game/components.h"
#include "engine/ecs.h"
#include "engine/math.h"
#include "engine/tilemap.h"

void
system_collision(void) {
  V2f *position = ecs_get_component_list("position");
  V2f *direction = ecs_get_component_list("direction");
  PositionLerp *position_lerp = ecs_get_component_list("position-lerp");
  bool *bump = ecs_get_component_list("bump");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if ((direction[e].x == 0 && direction[e].y == 0) || position_lerp[e].timer < 1.0f) continue;
    position_lerp[e].nxt = v2f_add(position[e], direction[e]);
    bool collided = true;
    if (tilemap_is_in_bounds(position_lerp[e].nxt)) {
      EntityReference collided_entity = tilemap_get(position_lerp[e].nxt);
      collided = collided_entity != 0;
    }
    if (collided) {
      bump[e] = true;
      position_lerp[e].nxt = v2f_add(position[e], v2f_muls(direction[e], 0.2f));
      position_lerp[e].prv = position[e];
      position_lerp[e].timer = 0.0f;
    } else {
      position_lerp[e].prv = position[e];
      position_lerp[e].timer = 0.0f;
    }
  }
}
