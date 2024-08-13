#include "engine/ecs.h"
#include "engine/types.h"
#include "game/components.h"
#include "general/global.h"

void
system_equip_type_none(usize entities_amount) {
  ItemInfo *item = ecs_get_component_list("item-info");
  for (Entity e = 0; e < entities_amount; e++) {
    if (global.game.items_cursor_id == global.menu.cursor_id     &&
        global.game.items_cursor_id == global.menu.cursor_id_prv &&
        global.game.item_type_page == item[e].type               &&
        global.menu.option_id[global.game.items_cursor_id] == item[e].id) {
      global.game.equip_type = EQUIP_NONE;
    }
  }
}

void
system_equip_type_weapon(usize entities_amount) {
  ItemInfo *item = ecs_get_component_list("item-info");
  for (Entity e = 0; e < entities_amount; e++) {
    if (global.game.items_cursor_id == global.menu.cursor_id     &&
        global.game.items_cursor_id == global.menu.cursor_id_prv &&
        global.game.item_type_page == item[e].type               &&
        global.menu.option_id[global.game.items_cursor_id] == item[e].id) {
      global.game.equip_type = EQUIP_WEAPON;
    }
  }
}

void
system_equip_type_shield(usize entities_amount) {
  ItemInfo *item = ecs_get_component_list("item-info");
  for (Entity e = 0; e < entities_amount; e++) {
    if (global.game.items_cursor_id == global.menu.cursor_id     &&
        global.game.items_cursor_id == global.menu.cursor_id_prv &&
        global.game.item_type_page == item[e].type               &&
        global.menu.option_id[global.game.items_cursor_id] == item[e].id) {
      global.game.equip_type = EQUIP_SHIELD;
    }
  }
}

void
system_equip_type_armour(usize entities_amount) {
  ItemInfo *item = ecs_get_component_list("item-info");
  for (Entity e = 0; e < entities_amount; e++) {
    if (global.game.items_cursor_id == global.menu.cursor_id     &&
        global.game.items_cursor_id == global.menu.cursor_id_prv &&
        global.game.item_type_page == item[e].type               &&
        global.menu.option_id[global.game.items_cursor_id] == item[e].id) {
      global.game.equip_type = EQUIP_ARMOUR;
    }
  }
}
