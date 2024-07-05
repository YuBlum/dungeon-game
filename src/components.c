#include "include/components.h"
#include "include/ecs.h"
#include "include/math.h"
#include "include/renderer.h"

void
components_create(void) {
  ecs_component_create(V2f, "position");
  ecs_component_create(MovePosition, "move-position");
  ecs_component_create(Color, "color");
}
