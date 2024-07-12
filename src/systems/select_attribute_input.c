#include "include/components.h"
#include "include/ecs.h"
#include "include/global.h"
#include "include/input.h"

void
select_attribute_input(void) {
  AttributeType *attribute_type = ecs_get_component_list("attribute-type");
  i32 *attribute_points = ecs_get_component_list("attribute-points");
  u32 *id = ecs_get_component_list("option-id");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    bool is_base_attribute = (global.class == CLASS_FIGHTER && attribute_type[e] == ATT_STRENGTH) ||
                             (global.class == CLASS_THIEF   && attribute_type[e] == ATT_AGILITY)  ||
                             (global.class == CLASS_WIZARD  && attribute_type[e] == ATT_INTELECT);
    if (global.class != global.class_prv) {
      if (is_base_attribute) {
        attribute_points[e] += 2;
        if (attribute_points[e] > 1) {
          global.total_attribute_points += attribute_points[e] - 1;
          attribute_points[e] = 1;
        }
      } else if ((global.class_prv == CLASS_FIGHTER && attribute_type[e] == ATT_STRENGTH) || 
                 (global.class_prv == CLASS_THIEF   && attribute_type[e] == ATT_AGILITY)  ||
                 (global.class_prv == CLASS_WIZARD  && attribute_type[e] == ATT_INTELECT)) {
        attribute_points[e] -= 2;
      }
    }
    if (global.cursor_id != cursor_id[e] || global.option_id[cursor_id[e]] != id[e] || cursor_id[e] != global.cursor_id_prv) continue;
    if (input_key_pressed(KEY_A)) {
      global.cursor_id = 0;
      continue;
    }
    if (input_key_pressed(KEY_UP) && attribute_points[e] < 1 && global.total_attribute_points > 0) {
      attribute_points[e]++;
      global.total_attribute_points--;
    }
    if (input_key_pressed(KEY_DOWN) && ((!is_base_attribute && attribute_points[e] > -2) || (is_base_attribute && attribute_points[e] > 0))) {
      attribute_points[e]--;
      global.total_attribute_points++;
    }
  }
  global.class_prv = global.class;
}
