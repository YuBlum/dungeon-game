#include "engine/ecs.h"
#include "engine/math.h"
#include "engine/renderer.h"
#include "game/components.h"
#include "general/core.h"
#include "general/global.h"

static const char *ammo_type_str[] = { "Rock", "Small Arrow", "Arrow", "Large Arrow" };
static const char *spell_type_str[] = { "regular spells", "complex spells", "extreme spells" };
static const char *potion_stats[] = { "HP", "EP" };

void
system_item_melee_description(usize entities_amount) {
  if (global.game.item_type_page != ITEM_TYPE_MELEE) return;
  ItemInfo *item = ecs_get_component_list("item-info");
  DiceTest *damage = ecs_get_component_list("dice-test");
  u32 *critical_hit = ecs_get_component_list("critical-hit");
  u32 *attribute_threshold = ecs_get_component_list("attribute-threshold");
  for (Entity e = 0; e < entities_amount; e++) {
    if (global.menu.option_id[global.game.items_cursor_id] != item[e].id) continue;
    f32 y = global.game.inventory_y - ((1 + PX_TO_UNIT * 3) * 5);
    renderer_text(V2F(0, y--), 1, true, false, 0x00ff00ff, 0, "Damage %ud%u+Strength", damage[e].amount, damage[e].faces);
    renderer_text(V2F(0, y--), 1, true, false, 0x00ff00ff, 0, "Crits at %u", critical_hit[e]);
    renderer_text(V2F(0, y--), 1, true, false, 0x00ff00ff, 0, "Strength required %u", attribute_threshold[e]);
  }
}

void
system_item_ranged_description(usize entities_amount) {
  if (global.game.item_type_page != ITEM_TYPE_RANGED) return;
  ItemInfo *item = ecs_get_component_list("item-info");
  DiceTest *damage = ecs_get_component_list("dice-test");
  u32 *attribute_threshold = ecs_get_component_list("attribute-threshold");
  AmmoType *ammo_type = ecs_get_component_list("ammo-type");
  u32 *critical_hit = ecs_get_component_list("critical-hit");
  for (Entity e = 0; e < entities_amount; e++) {
    if (global.menu.option_id[global.game.items_cursor_id] != item[e].id) continue;
    f32 y = global.game.inventory_y - ((1 + PX_TO_UNIT * 3) * 5);
    if (damage[e].add) {
      renderer_text(V2F(0, y--), 1, true, false, 0x00ff00ff, 0, "Damage %ud%u+%u", damage[e].amount, damage[e].faces, damage[e].add);
    } else {
      renderer_text(V2F(0, y--), 1, true, false, 0x00ff00ff, 0, "Damage %ud%u", damage[e].amount, damage[e].faces);
    }
    renderer_text(V2F(0, y--), 1, true, false, 0x00ff00ff, 0, "Crits at %u", critical_hit[e]);
    if (ammo_type[e] != AMMO_NONE) {
      renderer_text(V2F(0, y--), 1, true, false, 0x00ff00ff, 0, "Ammo type %s", ammo_type_str[ammo_type[e] - 1]);
    }
    renderer_text(V2F(0, y--), 1, true, false, 0x00ff00ff, 0, "Agility required %u", attribute_threshold[e]);
  }
}

void
system_item_staff_description(usize entities_amount) {
  if (global.game.item_type_page != ITEM_TYPE_STAFF) return;
  ItemInfo *item = ecs_get_component_list("item-info");
  u32 *attribute_threshold = ecs_get_component_list("attribute-threshold");
  Staff *staff = ecs_get_component_list("staff");
  for (Entity e = 0; e < entities_amount; e++) {
    if (global.menu.option_id[global.game.items_cursor_id] != item[e].id) continue;
    f32 y = global.game.inventory_y - ((1 + PX_TO_UNIT * 3) * 5);
    renderer_text(V2F(0, y--), 1, true, false, 0x00ff00ff, 0, "Can cast %s", spell_type_str[staff[e].spell_type]);
    if (staff[e].reduce_dt) {
      renderer_text(V2F(0, y--), 1, true, false, 0x00ff00ff, 0, "Reduce cast DT by %u", staff[e].reduce_dt);
    }
    renderer_text(V2F(0, y--), 1, true, false, 0x00ff00ff, 0, "Presence required %u", attribute_threshold[e]);
  }
}

void
system_item_defensive_description(usize entities_amount) {
  if (global.game.item_type_page != ITEM_TYPE_DEFENSIVE) return;
  ItemInfo *item = ecs_get_component_list("item-info");
  u32 *attribute_threshold = ecs_get_component_list("attribute-threshold");
  DefensiveItem *defensive = ecs_get_component_list("defensive-item");
  for (Entity e = 0; e < entities_amount; e++) {
    if (global.menu.option_id[global.game.items_cursor_id] != item[e].id) continue;
    f32 y = global.game.inventory_y - ((1 + PX_TO_UNIT * 3) * 5);
    renderer_text(V2F(0, y--), 1, true, false, 0x00ff00ff, 0, "+%u AP", defensive[e].extra_armour_points);
    renderer_text(V2F(0, y--), 1, true, false, 0x00ff00ff, 0, "Strength required %u", attribute_threshold[e]);
  }
}

void
system_item_potion_description(usize entities_amount) {
  if (global.game.item_type_page != ITEM_TYPE_POTION) return;
  ItemInfo *item = ecs_get_component_list("item-info");
  DiceTest *heal = ecs_get_component_list("dice-test");
  PotionType *potion_type = ecs_get_component_list("potion-type");
  for (Entity e = 0; e < entities_amount; e++) {
    if (global.menu.option_id[global.game.items_cursor_id] != item[e].id) continue;
    f32 y = global.game.inventory_y - ((1 + PX_TO_UNIT * 3) * 5);
    renderer_text(V2F(0, y--), 1, true, false, 0x00ff00ff, 0, "Heal %ud%u+%u %s", heal[e].amount, heal[e].faces, heal[e].add, potion_stats[potion_type[e]]);
  }
}
