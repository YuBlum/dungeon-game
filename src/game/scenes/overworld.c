#include "engine/input.h"
#include "engine/types.h"
#include "game/components.h"
#include "general/core.h"
#include "general/global.h"
#include "engine/tilemap.h"
#include "game/prefabs.h"
#include <math.h>
#include <string.h>

void
scene_overworld_on_start(void) {
  global.all.split_screen = true;
  global.game.removed_item = false;
  global.game.fixed_items_order = false;
  global.game.item_type_page = ITEM_TYPE_MELEE;
  memset(global.game.items_amount, 0, sizeof (u32) * ITEM_TYPE_AMOUNT);
  tilemap_setup(GAME_W, GAME_H);
  prefab_terminal();
  prefab_player(V2FS(1));
  prefab_item(ITEM_WOOD_SWORD, 99);
  prefab_item(ITEM_KNIFE, 99);
  prefab_item(ITEM_DAGGER, 99);
  prefab_item(ITEM_SHORTSWORD, 99);
  prefab_item(ITEM_HANDAXE, 99);
  prefab_item(ITEM_LONGSWORD, 99);
  prefab_item(ITEM_TRIDANT, 99);
  prefab_item(ITEM_WARHAMMER, 99);
  prefab_item(ITEM_GREATSWORD, 99);
  prefab_item(ITEM_BATTLEAXE, 99);
  prefab_item(ITEM_MAUL, 99);
  prefab_item(ITEM_DREAMSWORD, 99);
  prefab_item(ITEM_MASTERSWORD, 99);
  prefab_item(ITEM_GODS_WEAPON, 99);
  prefab_item(ITEM_SLINGSHOT, 99);
  prefab_item(ITEM_BIG_SLINGSHOT, 99);
  prefab_item(ITEM_SMALL_THROWING_KNIFE, 99);
  prefab_item(ITEM_SHORTBOW, 99);
  prefab_item(ITEM_THROWING_KNIFE, 99);
  prefab_item(ITEM_LIGHT_CROSSBOW, 99);
  prefab_item(ITEM_HAND_CROSSBOW, 99);
  prefab_item(ITEM_LONGBOW, 99);
  prefab_item(ITEM_HUNTING_BOW, 99);
  prefab_item(ITEM_HEAVY_CROSSBOW, 99);
  prefab_item(ITEM_MASTERBOW, 99);
  prefab_item(ITEM_KILLER_CROSSBOW, 99);
  prefab_item(ITEM_SMALL_STAFF, 99);
  prefab_item(ITEM_STAFF, 99);
  prefab_item(ITEM_BIG_STAFF, 99);
  prefab_item(ITEM_SMALL_SACRED_STAFF, 99);
  prefab_item(ITEM_SACRED_STAFF, 99);
  prefab_item(ITEM_ESSENCED_STAFF, 99);
  prefab_item(ITEM_BLESSED_TRUNK, 99);
  prefab_item(ITEM_EDEN_WOOD, 99);
  prefab_item(ITEM_DARKNESS_CANE, 99);
  prefab_item(ITEM_SPIRITS_GUIDANCE, 99);
  prefab_item(ITEM_ROCK, 99);
  prefab_item(ITEM_SMALL_ARROW, 99);
  prefab_item(ITEM_ARROW, 99);
  prefab_item(ITEM_LARGE_ARROW, 99);
  prefab_item(ITEM_WOOD_SHIELD, 99);
  prefab_item(ITEM_SMALL_METAL_SHIELD, 99);
  prefab_item(ITEM_METAL_SHIELD, 99);
  prefab_item(ITEM_STRONG_METAL_SHIELD, 99);
  prefab_item(ITEM_TITANIUM_SHIELD, 99);
  prefab_item(ITEM_LIGHT_ARMOUR, 99);
  prefab_item(ITEM_WEAK_METAL_ARMOUR, 99);
  prefab_item(ITEM_METAL_ARMOUR, 99);
  prefab_item(ITEM_STRONG_METAL_ARMOUR, 99);
  prefab_item(ITEM_TITANIUM_ARMOUR, 99);
  prefab_item(ITEM_SLIME_FLUID, 99);
  prefab_item(ITEM_SACRED_WOOD, 99);
  prefab_item(ITEM_UNDEAD_MEAT, 99);
  prefab_item(ITEM_SKULLWALKER_BONE, 99);
  prefab_item(ITEM_HOLY_WATER, 99);
  prefab_item(ITEM_ANIMAL_BLOOD, 99);
  prefab_item(ITEM_HUMAN_BLOOD, 99);
  prefab_item(ITEM_ANIMAL_ORGAN, 99);
  prefab_item(ITEM_HUMAN_ORGAN, 99);
  prefab_item(ITEM_LOCKPICK, 99);
  prefab_item(ITEM_ADVANCED_LOCKPICK, 99);
  prefab_item(ITEM_MAGICAL_LOCKPICK, 99);
  prefab_item(ITEM_HEALING_POTION, 99);
  prefab_item(ITEM_LARGE_HEALING_POTION, 99);
  prefab_item(ITEM_GREAT_HEALING_POTION, 99);
  prefab_item(ITEM_WILL_POTION, 99);
  prefab_item(ITEM_LARGE_WILL_POTION, 99);
  prefab_item(ITEM_GREAT_WILL_POTION, 99);
  prefab_pause();
}

void
scene_overworld_on_pre_systems(void) {
  global.menu.cursor_id_prv = global.menu.cursor_id;
  global.game.menu_type_prv = global.game.menu_type;
  if (global.game.menu_type == IGM_INVENTORY) {
    if (global.game.fixed_items_order) {
      global.game.removed_item = false;
      global.game.fixed_items_order = false;
    }
    global.menu.option_amount[global.game.items_cursor_id] = global.game.items_amount[global.game.item_type_page];
    if (global.menu.option_id[global.game.items_cursor_id] == global.game.items_amount[global.game.item_type_page]) {
      global.menu.option_id[global.game.items_cursor_id]--;
    }
    i32 move = input_key_pressed(KEY_RIGHT) - input_key_pressed(KEY_LEFT);
    if (move) {
      global.menu.option_id[global.game.items_cursor_id] = 0;
      global.game.items_offset = 0;
      global.game.items_cursor_min = 0;
      global.game.items_cursor_max = 3;
      if (global.game.item_type_page == 0 && move < 0) {
        global.game.item_type_page = ITEM_TYPE_AMOUNT - 1;
      } else if (global.game.item_type_page == ITEM_TYPE_AMOUNT - 1 && move > 0) {
        global.game.item_type_page = 0;
      } else {
        global.game.item_type_page += move;
      }
    }
  }
}

void
scene_overworld_on_draw(void) {
  const char *title;
  switch (global.game.menu_type) {
    case IGM_NONE:
      title = 0;
      break;
    case IGM_PAUSE:
      title = "~ PAUSED ~";
      break;
    case IGM_INVENTORY:
      title = "~ INVENTORY ~";
      break;
    case IGM_ABILITIES:
      title = "~ ABILITIES ~";
      break;
    case IGM_SPELLS:
      title = "~ SPELLS ~";
      break;
  }
  if (title) {
    global.game.inventory_y = UI_TOP - 1;
    renderer_text(V2F(0, global.game.inventory_y - PX_TO_UNIT), 1, true, false, 0xff5500ff, 1, "%s", title);
    renderer_text(V2F(0, global.game.inventory_y), 1, true, false, 0xffffaaff, 1, "%s", title);
  }

  if (global.game.menu_type == IGM_INVENTORY) {
    f32 y = global.game.inventory_y - 6;
    renderer_rect(V2F(UI_LEFT - PX_TO_UNIT * 2, y + PX_TO_UNIT * 2), V2F(UI_W + PX_TO_UNIT * 4, 1 + PX_TO_UNIT * 4), false, 0xffffffff, 1);
    renderer_rect(V2F(UI_LEFT - PX_TO_UNIT * 1, y + PX_TO_UNIT * 1), V2F(UI_W + PX_TO_UNIT * 2, 1 + PX_TO_UNIT * 2), false, 0x000000ff, 1);
    renderer_rect(V2F(UI_RIGHT - 2.0f, y + PX_TO_UNIT), V2F(PX_TO_UNIT, 1 + PX_TO_UNIT * 2), false, 0xffffffff, 1);
    renderer_text(V2F(UI_RIGHT - 1.625f, y - PX_TO_UNIT), 1, false, false, 0xff5500ff, 1, "@");
    renderer_text(V2F(UI_RIGHT - 1.625f, y), 1, false, false, 0xffffaaff, 1, "@");
    const char *page = 0;
    switch (global.game.item_type_page) {
      case ITEM_TYPE_MELEE:
        page = "Melee";
        break;
      case ITEM_TYPE_RANGED:
        page = "Ranged";
        break;
      case ITEM_TYPE_AMMO:
        page = "Ammo";
        break;
      case ITEM_TYPE_STAFF:
        page = "Staff";
        break;
      case ITEM_TYPE_DEFENSIVE:
        page = "Defensive";
        break;
      case ITEM_TYPE_LOCKPICK:
        page = "Lockpick";
        break;
      case ITEM_TYPE_POTION:
        page = "Potion";
        break;
      case ITEM_TYPE_MAGIC_COMPONENT:
        page = "Magic Component";
        break;
      case ITEM_TYPE_AMOUNT: break;
    }
    u32 space_amount = (sinf(global.all.time * 0.15f) + 1) * 1.5 + 1;
    renderer_text(V2F(UI_LEFT + (UI_W - 2.0f) * 0.5f, y - PX_TO_UNIT), 1, true, false, 0xff5500ff, 1, "<-%.*s%s%.*s->", space_amount, "|||", page, space_amount, "|||");
    renderer_text(V2F(UI_LEFT + (UI_W - 2.0f) * 0.5f, y), 1, true, false, 0xffffaaff, 1, "<-%.*s%s%.*s->", space_amount, "|||", page, space_amount, "|||");
  }
}
