#include "engine/ecs.h"
#include "engine/input.h"
#include "engine/types.h"
#include "game/components.h"
#include "general/core.h"
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


static void
select_equiped_item(usize entities_amount, SelectedItem *select, ItemEquipType equip_type) {
  ItemInfo *item = ecs_get_component_list("item-info");
  bool *equiped = ecs_get_component_list("item-equiped");
  Callback *get_player = ecs_get_component_list("callback");
  for (Entity e = 0; e < entities_amount; e++) {
    if (!input_key_pressed(KEY_A) || global.game.items_cursor_id != global.menu.cursor_id || global.game.items_cursor_id != global.menu.cursor_id_prv) continue;
    if (global.game.item_type_page != item[e].type || global.menu.option_id[global.game.items_cursor_id] != item[e].id) {
      if (global.game.equip_type == equip_type && equiped[e]) {
        equiped[e] = false;
      }
      continue;
    }
    (void)get_player;
    equiped[e] = true;
    select->has_item = true;
    select->type = item[e].type;
    select->id = 0;
    global.game.rearranged_item = true;
    global.game.changed_item_id = item[e].id;
  }
}

void
system_select_item_weapon(usize entities_amount) {
  if (global.game.menu_type_prv != IGM_INVENTORY) return;
  select_equiped_item(entities_amount, &global.game.weapon, EQUIP_WEAPON);
}

void
system_select_item_armour(usize entities_amount) {
  if (global.game.menu_type_prv != IGM_INVENTORY) return;
  select_equiped_item(entities_amount, &global.game.armour, EQUIP_ARMOUR);
}

void
system_select_item_shield(usize entities_amount) {
  if (global.game.menu_type_prv != IGM_INVENTORY) return;
  select_equiped_item(entities_amount, &global.game.shield, EQUIP_SHIELD);
}
