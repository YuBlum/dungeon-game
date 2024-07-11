#include "include/systems.h"
#include "include/ecs.h"

void
systems_create(void) {
  ecs_system_create(set_tile_system, ON_SCENE_START);
  ecs_system_must_have(set_tile_system, "position");

  ecs_system_create(input_direction_system, ON_UPDATE);
  ecs_system_must_have(input_direction_system, "direction", "input");

  ecs_system_create(collision_system, ON_UPDATE);
  ecs_system_must_have(collision_system, "position", "direction", "position-lerp", "bump");

  ecs_system_create(movement_system, ON_UPDATE);
  ecs_system_must_have(movement_system, "bump");

  ecs_system_create(draw_rect_system, ON_DRAW_GAME);
  ecs_system_must_have(draw_rect_system, "color");

  ecs_system_create(draw_char_sheet_system, ON_DRAW_UI);
  ecs_system_must_have(draw_char_sheet_system, "attributes", "defensive-stats", "char-sheet");

  ecs_system_create(draw_option_system, ON_DRAW_SCREEN);
  ecs_system_must_have(draw_option_system, "position", "name", "option-id");

  ecs_system_create(hover_on_option_system, ON_UPDATE);
  ecs_system_must_have(hover_on_option_system, "cursor");

  ecs_system_create(select_option_system, ON_UPDATE);
  ecs_system_must_have(select_option_system, "option-callback", "option-id");
}
