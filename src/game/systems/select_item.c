#include "engine/ecs.h"
#include "engine/input.h"
#include "engine/types.h"
#include "game/components.h"
#include "general/global.h"

void
system_select_item(usize entities_amount) {
  if (global.game.menu_type_prv != IGM_INVENTORY) return;
  Item *item = ecs_get_component_list("item");
  for (Entity e = 0; e < entities_amount; e++) {
    if (global.game.items_cursor_id == global.menu.cursor_id             &&
        global.game.items_cursor_id == global.menu.cursor_id_prv         &&
        global.menu.option_id[global.game.items_cursor_id] == item[e].id &&
        input_key_pressed(KEY_A)) {
      ecs_entity_destroy(e);
    }
  }
}
