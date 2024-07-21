#include "engine/ecs.h"
#include "game/components.h"
#include "general/global.h"
void
system_item_melee_description(void) {
  if (global.game.menu_type != IGM_INVENTORY) return;
  ItemInfo *item = ecs_get_component_list("item-info");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
  }
}
