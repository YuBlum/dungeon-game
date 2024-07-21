#include "engine/ecs.h"
#include "engine/types.h"
#include "game/components.h"
#include "general/global.h"

void
system_grow_items_amount(usize entities_amount) {
  for (Entity e = 0; e < entities_amount; e++) {
    if (ecs_entity_is_first_frame(e)) global.game.items_amount++;
  }
}

void
system_shrink_items_amount(usize entities_amount) {
  Item *item = ecs_get_component_list("item");
  for (Entity e = 0; e < entities_amount; e++) {
    if (!ecs_entity_is_last_frame(e)) continue;
    global.game.items_amount--;
    global.game.deleted_item = true;
    global.game.fixed_items_order = false;
    global.game.changed_item_id = item[e].id;
  }
}

