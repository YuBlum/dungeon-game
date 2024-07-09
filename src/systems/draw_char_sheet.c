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
    V2f pos = { -renderer_text_dimensions(1, "Character Sheet").x * 0.5f, UI_TOP };
    renderer_text(pos, 1, false, BORDER_COLOR, 0, "Character Sheet");
    pos.y -= 1 + PX_TO_UNIT;
    pos.x = UI_LEFT;
    renderer_rect(pos, V2F(UI_W, PX_TO_UNIT), false, BORDER_COLOR, 0);

    pos.y -= PX_TO_UNIT*4;
    pos.x = UI_LEFT + 2 * PX_TO_UNIT;
    for (u32 i = 0; i < 5; i++) {
      renderer_text(pos, 1, false, BORDER_COLOR, 0, "%s", attrib_names[i]);
      renderer_text(v2f_add(pos, V2F(3*PX_TO_UNIT, -1)), 1, false, 0xffff00ff, 0, "%+d", ((i32 *)&attributes[e])[i]);
      pos.x += 3.78125;
    }

    pos.y -= 3;
    pos.x = UI_LEFT + 0.75f;
    V2f prv_pos = pos;
    V2f siz = { 4, 2.5f };
    renderer_rect(pos, siz, false, 0xffffffff, 0);
    renderer_rect(v2f_add(pos, V2F(PX_TO_UNIT, -PX_TO_UNIT)) , v2f_subs(siz, 2*PX_TO_UNIT), false, 0x000000ff, 0);
    pos.y -= PX_TO_UNIT;
    pos.x += siz.x * 0.5f - renderer_text_dimensions(1, "# HP").x * 0.5f;
    renderer_text(pos, 1, false, BORDER_COLOR, 0, "# HP");
    pos.y -= 1;
    pos.x = prv_pos.x + siz.x * 0.5f - renderer_text_dimensions(1, "%.2u/%.2u", defensive_stats[e].hit_points_cur, defensive_stats[e].hit_points_max).x * 0.5f + PX_TO_UNIT;
    renderer_text(pos, 1, false, 0xffff00ff, 0, "%.2u/%.2u", defensive_stats[e].hit_points_cur, defensive_stats[e].hit_points_max);

    prv_pos.x +=  siz.x + 2;
    pos = prv_pos;
    renderer_rect(pos, siz, false, 0xffffffff, 0);
    renderer_rect(v2f_add(pos, V2F(PX_TO_UNIT, -PX_TO_UNIT)) , v2f_subs(siz, 2*PX_TO_UNIT), false, 0x000000ff, 0);
    pos.y -= PX_TO_UNIT;
    pos.x += siz.x * 0.5f - renderer_text_dimensions(1, "& FP").x * 0.5f;
    renderer_text(pos, 1, false, BORDER_COLOR, 0, "& FP");
    pos.y -= 1;
    pos.x = prv_pos.x + siz.x * 0.5f - renderer_text_dimensions(1, "%.2u/%.2u", general_stats[e].food_points_cur, general_stats[e].food_points_max).x * 0.5f + PX_TO_UNIT;
    renderer_text(pos, 1, false, 0xffff00ff, 0, "%.2u/%.2u", general_stats[e].food_points_cur, general_stats[e].food_points_max);

    prv_pos.x +=  siz.x + 2;
    pos = prv_pos;
    renderer_rect(pos, siz, false, 0xffffffff, 0);
    renderer_rect(v2f_add(pos, V2F(PX_TO_UNIT, -PX_TO_UNIT)) , v2f_subs(siz, 2*PX_TO_UNIT), false, 0x000000ff, 0);
    pos.y -= PX_TO_UNIT;
    pos.x += siz.x * 0.5f - renderer_text_dimensions(1, "` EP").x * 0.5f;
    renderer_text(pos, 1, false, BORDER_COLOR, 0, "` EP");
    pos.y -= 1;
    pos.x = prv_pos.x + siz.x * 0.5f - renderer_text_dimensions(1, "%.2u/%.2u", general_stats[e].essence_points_cur, general_stats[e].essence_points_max).x * 0.5f + PX_TO_UNIT;
    renderer_text(pos, 1, false, 0xffff00ff, 0, "%.2u/%.2u", general_stats[e].essence_points_cur, general_stats[e].essence_points_max);
  }
}
