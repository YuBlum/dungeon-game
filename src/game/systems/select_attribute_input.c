#include "game/components.h"
#include "general/global.h"
#include "engine/ecs.h"
#include "engine/input.h"

void
system_select_attribute_input(usize entities_amount) {
  AttributeType *attribute_type = ecs_get_component_list("attribute-type");
  i32 *attribute_points = ecs_get_component_list("attribute-points");
  u32 *id = ecs_get_component_list("option-id");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  for (Entity e = 0; e < entities_amount; e++) {
    bool is_base_attribute = (global.character_creation.class == CLASS_FIGHTER && attribute_type[e] == ATT_STRENGTH) ||
                             (global.character_creation.class == CLASS_THIEF   && attribute_type[e] == ATT_AGILITY)  ||
                             (global.character_creation.class == CLASS_WIZARD  && attribute_type[e] == ATT_INTELECT);
    if (global.character_creation.class != global.character_creation.class_prv) {
      if (is_base_attribute) {
        attribute_points[e] += 2;
        if (attribute_points[e] > 1) {
          global.character_creation.total_attribute_points += attribute_points[e] - 1;
          attribute_points[e] = 1;
        }
      } else if ((global.character_creation.class_prv == CLASS_FIGHTER && attribute_type[e] == ATT_STRENGTH) || 
                 (global.character_creation.class_prv == CLASS_THIEF   && attribute_type[e] == ATT_AGILITY)  ||
                 (global.character_creation.class_prv == CLASS_WIZARD  && attribute_type[e] == ATT_INTELECT)) {
        attribute_points[e] -= 2;
      }
    }
    if (global.menu.cursor_id != cursor_id[e] || global.menu.option_id[cursor_id[e]] != id[e] || cursor_id[e] != global.menu.cursor_id_prv) continue;
    if (input_key_pressed(KEY_A)) {
      global.menu.cursor_id = 0;
      continue;
    }
    if (input_key_pressed(KEY_UP) && attribute_points[e] < 1 && global.character_creation.total_attribute_points > 0) {
      attribute_points[e]++;
      global.character_creation.total_attribute_points--;
    }
    if (input_key_pressed(KEY_DOWN) && ((!is_base_attribute && attribute_points[e] > -2) || (is_base_attribute && attribute_points[e] > 0))) {
      attribute_points[e]--;
      global.character_creation.total_attribute_points++;
    }
  }
  global.character_creation.class_prv = global.character_creation.class;
}
