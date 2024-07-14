#include "engine/ecs.h"
#include "engine/math.h"
#include "engine/renderer.h"
#include "game/components.h"
#include "general/core.h"

void
system_draw_terminal(void) {
  Terminal *terminal = ecs_get_component_list("terminal");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    V2f position = V2F(UI_LEFT + PX_TO_UNIT, 0);
    for (u32 i = 0; i < TERMINAL_LINE_CAP; i++) {
      renderer_text(position, 1, false, false, 0xffffffff, 0, "> %.*s", terminal[e].line_size[i], terminal[e].line_buff[i]);
      position.y--;
    }
  }
}
