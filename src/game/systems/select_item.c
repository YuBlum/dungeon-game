#include "engine/ecs.h"
#include "engine/input.h"
#include "engine/types.h"
#include "game/components.h"
#include "general/global.h"

void
system_select_item(usize entities_amount) {
  return;
  if (global.game.menu_type_prv != IGM_INVENTORY) return;
  ItemInfo *item = ecs_get_component_list("item-info");
  for (Entity e = 0; e < entities_amount; e++) {
    if (global.game.item_type_page  == item[e].type                      &&
        global.game.items_cursor_id == global.menu.cursor_id             &&
        global.game.items_cursor_id == global.menu.cursor_id_prv         &&
        global.menu.option_id[global.game.items_cursor_id] == item[e].id &&
        input_key_pressed(KEY_A)) {
      ecs_entity_destroy(e);
    }
  }
}

void
system_select_item_weapon(usize entities_amount) {
  if (global.game.menu_type_prv != IGM_INVENTORY) return;
  ItemInfo *item = ecs_get_component_list("item-info");
  bool *equiped = ecs_get_component_list("item-equiped");
  Callback *get_player = ecs_get_component_list("callback");
  for (Entity e = 0; e < entities_amount; e++) {
    if (!input_key_pressed(KEY_A) || global.game.items_cursor_id != global.menu.cursor_id || global.game.items_cursor_id != global.menu.cursor_id_prv) continue;
    if (global.game.item_type_page != item[e].type || global.menu.option_id[global.game.items_cursor_id] != item[e].id) {
      if (equiped[e]) equiped[e] = false;
      continue;
    }
    (void)get_player;
    equiped[e] = true;
    global.game.weapon.has_item = true;
    global.game.weapon.type = item[e].type;
    global.game.weapon.id = 0;
    global.game.rearrenged_item = true;
    global.game.changed_item_id = item[e].id;
  }
}
