#include "game/components.h"
#include "engine/ecs.h"
#include "engine/math.h"
#include "engine/renderer.h"

void
system_draw_menu_hint(void) {
  V2f *position = ecs_get_component_list("position");
  Color *color = ecs_get_component_list("color");
  Tag *tag = ecs_get_component_list("tag");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    renderer_text(position[e], 1, true, true, color[e], 0, "%s", tag[e]);
  }
}
