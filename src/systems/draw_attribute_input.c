#include "include/components.h"
#include "include/core.h"
#include "include/ecs.h"
#include "include/global.h"
#include "include/math.h"
#include "include/renderer.h"

static const char *attrib_names[] = { "Agility", "Intelect", "Presence", "Strength", "Vigor", };

void
draw_attribute_input_system(void) {
  V2f *position = ecs_get_component_list("position");
  AttributeType *attribute_type = ecs_get_component_list("attribute-type");
  i32 *attribute_points = ecs_get_component_list("attribute-points");
  u32 *id = ecs_get_component_list("option-id");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    Color color =  0xffffffff;
    char *select_start = "";
    char *select_end = "";
    if (id[e] == global.option_id[cursor_id[e]] && global.cursor_id == cursor_id[e]) {
      color = 0xffff00ff;
      select_start = "> ";
      select_end = " <";
    }
    renderer_text(position[e], 1, true, true, color, 0, "%s%s%s", select_start, attrib_names[attribute_type[e]], select_end);
    V2f pos = v2f_sub(position[e], V2F(PX_TO_UNIT, 2.0f));
    renderer_rect(pos, V2F(1+PX_TO_UNIT*6, 1+PX_TO_UNIT*6), true, color, 0);
    renderer_rect(pos, V2F(1+PX_TO_UNIT*4, 1+PX_TO_UNIT*4), true, 0x000000ff, 0);
    renderer_text(pos, 1, true, true, color, 0, "%+d", attribute_points[e]);
  }
}
