#include "engine/ecs.h"
#include "engine/math.h"
#include "engine/renderer.h"
#include "engine/types.h"

void
system_draw_rect(usize entities_amount) {
  V2f *position = ecs_get_component_list("position");
  Color *color = ecs_get_component_list("color");
  for (Entity e = 0; e < entities_amount; e++) {
    renderer_rect(position[e], V2FS(1), true, color[e], 0);
  }
}
