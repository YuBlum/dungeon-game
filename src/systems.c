#include "include/components.h"
#include "include/ecs.h"
#include "include/global.h"
#include "include/input.h"
#include "include/math.h"
#include "include/renderer.h"
#include "include/tilemap.h"

static void
system_move_by_input(void) {
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
      if (tilemap_get(position_interpolation[e].nxt) == TILE_NONE) {
        position_interpolation[e].prv = position[e];
        position_interpolation[e].timer = 0.0f;
      } else {
        bump[e] = true;
        position_interpolation[e].nxt = v2f_add(position[e], v2f_muls(dir, 0.3f));
        position_interpolation[e].prv = position[e];
        position_interpolation[e].timer = 0.0f;
      }
    }
  }
}

static void
system_apply_movement(void) {
  V2f *position = ecs_get_component_list("position");
  PositionInterpolation *position_interpolation = ecs_get_component_list("position-interpolation");
  f32 *speed = ecs_get_component_list("speed");
  TileType *tile_type = ecs_get_component_list("tile-type");
  bool *bump = ecs_get_component_list("bump");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (position_interpolation[e].timer >= 1.0f) continue;
    if (!bump[e]) {
      if (position_interpolation[e].timer == 0.0f) {
        tilemap_set(position_interpolation[e].prv, TILE_NONE, false);
        tilemap_set(position_interpolation[e].nxt, tile_type[e], false);
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

static void
system_draw_rect(void) {
  V2f *position = ecs_get_component_list("position");
  Color *color = ecs_get_component_list("color");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    renderer_request_quad(position[e], V2FS(1), color[e], 0);
  }
}

void
systems_create(void) {
  ecs_system_create(system_move_by_input, SYS_UPDATE);
  ecs_system_must_have(system_move_by_input, "input", "position", "position-interpolation", "bump");

  ecs_system_create(system_apply_movement, SYS_UPDATE);
  ecs_system_must_have(system_apply_movement, "position", "position-interpolation", "speed", "bump", "tile-type");

  ecs_system_create(system_draw_rect, SYS_DRAW);
  ecs_system_must_have(system_draw_rect, "position", "color");
}
