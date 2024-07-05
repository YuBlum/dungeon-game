#include "include/components.h"
#include "include/core.h"
#include "include/ecs.h"
#include "include/global.h"
#include "include/input.h"
#include "include/math.h"
#include "include/renderer.h"
#include "include/tilemap.h"

static void
system_move_by_input(void) {
  V2f *position = ecs_get_component_list("position");
  MovePosition *move_position = ecs_get_component_list("move-position");
  bool *input = ecs_get_component_list("input");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (!input[e] || move_position[e].timer < 1.0f) continue;
    V2f dir = {
      input_key_pressed(KEY_RIGHT) - input_key_pressed(KEY_LEFT),
      input_key_pressed(KEY_UP)    - input_key_pressed(KEY_DOWN)

    };
    if ((dir.x != 0 || dir.y != 0) && (dir.x == 0 || dir.y == 0)) {
      move_position[e].nxt = v2f_add(position[e], dir);
      if (tilemap_get(move_position[e].nxt) != TILE_SOLID) {
        move_position[e].prv = position[e];
        move_position[e].timer = 0.0f;
      }
    }
  }
}

static void
system_apply_movement(void) {
  V2f *position = ecs_get_component_list("position");
  MovePosition *move_position = ecs_get_component_list("move-position");
  TileType *tile_type = ecs_get_component_list("tile-type");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (move_position[e].timer >= 1.0f) continue;
    else if (move_position[e].timer == 0.0f) {
      tilemap_set(move_position[e].prv, TILE_NONE, false);
      tilemap_set(move_position[e].nxt, tile_type[e], false);
    }
    move_position[e].timer += global.dt * move_position[e].speed;
    if (move_position[e].timer >= 1.0f) {
      position[e] = move_position[e].nxt;
    } else {
      position[e] = v2f_lerp(move_position[e].prv, move_position[e].nxt, smoothstep(0, 1, move_position[e].timer));
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
  ecs_system_must_have(system_move_by_input, "input", "position", "move-position");

  ecs_system_create(system_apply_movement, SYS_UPDATE);
  ecs_system_must_have(system_apply_movement, "position", "move-position", "tile-type");

  ecs_system_create(system_draw_rect, SYS_DRAW);
  ecs_system_must_have(system_draw_rect, "position", "color");
}
