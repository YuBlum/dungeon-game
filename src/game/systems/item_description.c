#include "engine/ecs.h"
#include "engine/math.h"
#include "engine/renderer.h"
#include "game/components.h"
#include "general/core.h"
#include "general/global.h"

void
system_item_melee_description(usize entities_amount) {
  if (global.game.item_type_page != ITEM_TYPE_MELEE) return;
  ItemInfo *item = ecs_get_component_list("item-info");
  DiceTest *damage = ecs_get_component_list("dice-test");
  u32 *attribute_threshold = ecs_get_component_list("attribute-threshold");
  for (Entity e = 0; e < entities_amount; e++) {
    if (global.menu.option_id[global.game.items_cursor_id] != item[e].id) continue;
    f32 y = global.game.inventory_y - ((1 + PX_TO_UNIT * 3) * 5);
    renderer_text(V2F(0, y--), 1, true, false, 0x00ff00ff, 0, "Damage %ud%u+Strength", damage[e].amount, damage[e].faces);
    renderer_text(V2F(0, y), 1, true, false, 0x00ff00ff, 0, "Strength Required %u", attribute_threshold[e]);
  }
}
