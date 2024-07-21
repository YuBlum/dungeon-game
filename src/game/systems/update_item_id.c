#include "engine/ecs.h"
#include "engine/types.h"
#include "game/components.h"
#include "general/global.h"

void
system_update_item_id(usize entities_amount) {
  if (!global.game.deleted_item) return;
  global.game.fixed_items_order = true;
  Item *item = ecs_get_component_list("item");
  for (Entity e = 0; e < entities_amount; e++) {
    if (item[e].id > global.game.changed_item_id) {
      item[e].id--;
    }
  }
}
