#include "engine/ecs.h"
#include "general/global.h"

void
system_update_items_amount(void) {
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    global.game.items_amount++;
  }
}
