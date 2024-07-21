#include "engine/ecs.h"
#include "engine/types.h"
#include "game/components.h"
#include "general/global.h"

void
system_remove_item(usize entities_amount) {
  ItemInfo *item = ecs_get_component_list("item-info");
  for (Entity e = 0; e < entities_amount; e++) {
    if (!ecs_entity_is_last_frame(e)) continue;
    global.game.items_amount[global.game.item_type_page]--;
    global.game.removed_item = true;
    global.game.changed_item_id = item[e].id;
  }
}

