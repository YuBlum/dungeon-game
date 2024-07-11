#include "include/components.h"
#include "include/ecs.h"
#include "include/math.h"
#include "include/renderer.h"

void
components_create(void) {
  ecs_component_create(V2f, "position");
  ecs_component_create(V2f, "direction");
  ecs_component_create(PositionLerp, "position-lerp");
  ecs_component_create(f32, "speed");
  ecs_component_create(Color, "color");
  ecs_component_create(bool, "bump");
  ecs_component_create(Attributes, "attributes");
  ecs_component_create(DefensiveStats, "defensive-stats");
  ecs_component_create(CharSheet, "char-sheet");
  ecs_component_create(OptionCallback, "option-callback");
  ecs_component_create(const char *, "name");
  ecs_component_create(i32, "option-id");
  ecs_component_create(i32, "cursor");

  ecs_empty_component_create("input");
}
