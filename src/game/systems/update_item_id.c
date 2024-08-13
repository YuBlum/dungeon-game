#include "engine/ecs.h"
#include "engine/types.h"
#include "game/components.h"
#include "general/global.h"
#include "general/core.h"

void
system_update_item_id(usize entities_amount) {
  global.game.fixed_items_order = true;
  ItemInfo *item = ecs_get_component_list("item-info");
  for (Entity e = 0; e < entities_amount; e++) {
    if (item[e].type != global.game.item_type_page) continue;
    if (global.game.removed_item && item[e].id > global.game.changed_item_id) {
      item[e].id--;
    }
    if (global.game.rearranged_item && item[e].id < global.game.changed_item_id) {
      item[e].id++;
    }
  }
}

static void
update_equiped_item_id(usize entities_amount, u32 selected_id) {
  ItemInfo *item = ecs_get_component_list("item-info");
  bool *equiped = ecs_get_component_list("item-equiped");
  for (Entity e = 0; e < entities_amount; e++) {
    if (item[e].type == global.game.item_type_page && equiped[e] && item[e].id == global.game.changed_item_id) {
      item[e].id = selected_id;
      global.menu.option_id[global.game.items_cursor_id] = selected_id;
      global.game.items_offset = 0;
      global.game.items_cursor_min = 0;
      global.game.items_cursor_max = 3;
    }
  }
}

void
system_update_weapon_item_id(usize entities_amount) {
  if (!global.game.rearranged_item) return;
  update_equiped_item_id(entities_amount, global.game.weapon.id);
}

void
system_update_armour_item_id(usize entities_amount) {
  if (!global.game.rearranged_item) return;
  update_equiped_item_id(entities_amount, global.game.armour.id);
}

void
system_update_shield_item_id(usize entities_amount) {
  if (!global.game.rearranged_item) return;
  update_equiped_item_id(entities_amount, global.game.shield.id);
}
