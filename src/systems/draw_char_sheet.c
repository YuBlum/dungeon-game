#include "include/components.h"
#include "include/core.h"
#include "include/ecs.h"
#include "include/renderer.h"

static const char *attrib_names[] = { "AGI", "INT", "PRE", "STR", "VIG", };
static const char *class_names[] = { "Fighter", "Thief", "Wizard" };

void
draw_char_sheet_system(void) {
  Attributes *attributes = ecs_get_component_list("attributes");
  CharSheet *char_sheet = ecs_get_component_list("char-sheet");
  DefensiveStats *defensive_stats = ecs_get_component_list("defensive-stats");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    (void)attributes;
    (void)char_sheet;
    (void)defensive_stats;
    V2f pos = { -renderer_text_dimensions(1, "%s", char_sheet[e].name).x * 0.5f, UI_TOP };
    renderer_text(pos, 1, false, false, 0xffff00ff, 0, "%s", char_sheet[e].name);
    pos.y -= 1 + PX_TO_UNIT;
    pos.x = UI_LEFT;
    renderer_rect(pos, V2F(UI_W, PX_TO_UNIT), false, BORDER_COLOR, 0);

    pos.y -= PX_TO_UNIT*4;
    pos.x = UI_LEFT + 2 * PX_TO_UNIT;
    for (u32 i = 0; i < 5; i++) {
      renderer_text(pos, 1, false, false, BORDER_COLOR, 0, "%s", attrib_names[i]);
      renderer_text(v2f_add(pos, V2F(3*PX_TO_UNIT, -1)), 1, false, false, 0xffff00ff, 0, "%+d", ((i32 *)&attributes[e])[i]);
      pos.x += 3.78125f;
    }

    pos.y -= 2.5f;
    pos.x = UI_LEFT;
    renderer_rect(pos, V2F(UI_W, PX_TO_UNIT), false, BORDER_COLOR, 0);

    pos.y -= 0.5f;
    pos.x = UI_LEFT + 0.5f;
    renderer_text(pos, 1, false, false, BORDER_COLOR, 0, "# HP");
    renderer_text(v2f_add(pos, V2F(3.75f, 0)), 1, false, false, 0xffff00ff, 0, "%.2d/%.2d", defensive_stats[e].hit_points_cur, defensive_stats[e].hit_points_max);

    pos.y -= 1.5f;
    renderer_text(pos, 1, false, false, BORDER_COLOR, 0, "` EP");
    renderer_text(v2f_add(pos, V2F(3.75f, 0)), 1, false, false, 0xffff00ff, 0, "%.2d/%.2d", char_sheet[e].essence_points_cur, char_sheet[e].essence_points_max);

    pos.x = UI_RIGHT - 7.5f - PX_TO_UNIT;
    pos.y += 1.5f;
    renderer_text(pos, 1, false, false, BORDER_COLOR, 0, "\\ AP");
    renderer_text(v2f_add(pos, V2F(4.75f, 0)), 1, false, false, 0xffff00ff, 0, "%.2d", defensive_stats[e].armour_points);

    pos.y -= 1.5f;
    renderer_text(pos, 1, false, false, BORDER_COLOR, 0, "& FP");
    renderer_text(v2f_add(pos, V2F(3.75f, 0)), 1, false, false, 0xffff00ff, 0, "%.2d/%.2d", char_sheet[e].food_points_cur, char_sheet[e].food_points_max);


    pos.y -= 1.5f;
    pos.x = UI_LEFT;
    renderer_rect(pos, V2F(UI_W, PX_TO_UNIT), false, BORDER_COLOR, 0);

    pos.x += UI_W * 0.5f;
    pos.y += 3.5f;
    renderer_rect(pos, V2F(PX_TO_UNIT, 3.5f), false, BORDER_COLOR, 0);

    pos.y -= 4.0f + PX_TO_UNIT;
    pos.x = UI_LEFT + 0.5f;
    V2f siz = { 3.5f, 2.0f+2*PX_TO_UNIT };
    renderer_rect(pos, siz, 0, BORDER_COLOR, 0);
    pos.x += PX_TO_UNIT;
    pos.y -= PX_TO_UNIT;
    siz = v2f_subs(siz, 2*PX_TO_UNIT);
    renderer_rect(pos, siz, 0, 0x000000ff, 0);
    renderer_text(v2f_add(pos, V2F(siz.x * 0.5f - 1, 0)), 1, false, false, BORDER_COLOR, 0, "LVL");
    pos.y--;
    renderer_text(v2f_add(pos, V2F(siz.x * 0.5f - 0.75f, 0)), 1, false, false, 0xffff00ff, 0, "%.2u", char_sheet[e].level);


    pos.y += PX_TO_UNIT + 1;
    renderer_text(
      V2F(-renderer_text_dimensions(1, "~ %s ~", class_names[char_sheet[e].class]).x *0.5f, pos.y - 0.5f),
      1, false, false, BORDER_COLOR, 0, "~ %s ~", class_names[char_sheet[e].class]);

    siz = v2f_adds(siz, 2*PX_TO_UNIT);
    pos.x = UI_RIGHT - siz.y - 2.0f;
    renderer_rect(pos, siz, 0, BORDER_COLOR, 0);
    pos.x += PX_TO_UNIT;
    pos.y -= PX_TO_UNIT;
    siz = v2f_subs(siz, 2*PX_TO_UNIT);
    renderer_rect(pos, siz, 0, 0x000000ff, 0);
    renderer_text(v2f_add(pos, V2F(siz.x * 0.5f - 1, 0)), 1, false, false, BORDER_COLOR, 0, "EXP");
    pos.y--;
    renderer_text(v2f_add(pos, V2F(siz.x * 0.5f - 1, 0)), 1, false, false, 0xffff00ff, 0, "%.3u", char_sheet[e].experience);

    pos.y -= siz.y - 0.25f;
    pos.x = UI_LEFT;
    renderer_rect(pos, V2F(UI_W, PX_TO_UNIT), false, BORDER_COLOR, 0);
  }
}
