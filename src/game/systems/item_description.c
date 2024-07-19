#include "engine/ecs.h"
#include "game/components.h"
#include "general/global.h"
void
system_melee_item_description(void) {
  if (global.game.menu_type != IGM_INVENTORY) return;
  Item *item = ecs_get_component_list("item");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    item[e].id
  }
}
