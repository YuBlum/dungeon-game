#include "include/components.h"
#include "include/core.h"
#include "include/ecs.h"
#include "include/renderer.h"

static const char *attrib_names[] = { "AGI", "INT", "PRE", "STR", "VIG", };

void
draw_char_sheet_system(void) {
  Attributes *attributes = ecs_get_component_list("attributes");
  GeneralStats *general_stats = ecs_get_component_list("general-stats");
  DefensiveStats *defensive_stats = ecs_get_component_list("defensive-stats");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    (void)attributes;
    (void)general_stats;
    (void)defensive_stats;
    V2f pos = { -renderer_text_dimensions(1, "Attributes").x * 0.5f, UI_TOP };
    renderer_text(pos, 1, false, BORDER_COLOR, 0, "Attributes");

    pos.y -= 1 + PX_TO_UNIT;
    pos.x = UI_LEFT;
    renderer_rect(pos, V2F(UI_W, GAME_BORDER_PX*PX_TO_UNIT), false, BORDER_COLOR, 0);

    pos.y -= PX_TO_UNIT*2;
    pos.x = UI_LEFT + 2 * PX_TO_UNIT;
    for (u32 i = 0; i < 5; i++) {
      renderer_text(pos, 1, false, BORDER_COLOR, 0, "%s", attrib_names[i]);
      renderer_text(v2f_add(pos, V2F(3.0f, 0)), 1, false, 0xffff00ff, 0, "%d", ((i32 *)&attributes[e])[i]);
      pos.y -= 1 + PX_TO_UNIT;
    }
  }
}
