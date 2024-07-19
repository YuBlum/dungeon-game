#include "engine/ecs.h"
#include "general/global.h"

void
system_update_items_amount(usize entities_amount) {
  for (Entity e = 0; e < entities_amount; e++) {
    if (ecs_entity_is_first_frame(e)) global.game.items_amount++;
  }
}
