#include "engine/ecs.h"
#include "engine/types.h"
#include "general/global.h"

void
system_grow_items_amount(usize entities_amount) {
  for (Entity e = 0; e < entities_amount; e++) {
    if (ecs_entity_is_first_frame(e)) global.game.items_amount++;
  }
}

void
system_shrink_items_amount(usize entities_amount) {
  for (Entity e = 0; e < entities_amount; e++) {
    if (ecs_entity_is_last_frame(e)) global.game.items_amount--;
  }
}

