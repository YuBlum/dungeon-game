#include "include/components.h"
#include "include/ecs.h"
#include "include/math.h"
#include "include/renderer.h"

void
components_create(void) {
  ecs_component_create(V2f, "position");
  ecs_component_create(PositionInterpolation, "position-interpolation");
  ecs_component_create(f32, "speed");
  ecs_component_create(Color, "color");
  ecs_component_create(bool, "bump");

  ecs_empty_component_create("input");
}
