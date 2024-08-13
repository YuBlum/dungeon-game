#include "engine/input.h"
#include "engine/types.h"
#include "game/components.h"
#include "general/core.h"
#include "general/global.h"
#include "engine/tilemap.h"
#include "game/prefabs.h"
#include <math.h>
#include <string.h>

static EntityReference player;

static void
get_player_callback(EntityReference *ref) {
  *ref = player;
}

void
scene_overworld_on_start(void) {
  global.all.split_screen = true;
  global.game.removed_item = false;
  global.game.rearranged_item = false;
  global.game.fixed_items_order = false;
  global.game.item_type_page = ITEM_TYPE_MELEE;
  global.game.equip_type = EQUIP_WEAPON;
  memset(global.game.items_amount, 0, sizeof (u32) * ITEM_TYPE_AMOUNT);
  tilemap_setup(GAME_W, GAME_H);
  prefab_terminal();
  prefab_player(V2FS(1), &player);
  prefab_item(ITEM_WOOD_SWORD, (Callback)get_player_callback, 99);
  prefab_item(ITEM_KNIFE, (Callback)get_player_callback, 99);
  prefab_item(ITEM_DAGGER, (Callback)get_player_callback, 99);
  prefab_item(ITEM_SHORTSWORD, (Callback)get_player_callback, 99);
  prefab_item(ITEM_HANDAXE, (Callback)get_player_callback, 99);
  prefab_item(ITEM_LONGSWORD, (Callback)get_player_callback, 99);
  prefab_item(ITEM_TRIDANT, (Callback)get_player_callback, 99);
  prefab_item(ITEM_WARHAMMER, (Callback)get_player_callback, 99);
  prefab_item(ITEM_GREATSWORD, (Callback)get_player_callback, 99);
  prefab_item(ITEM_BATTLEAXE, (Callback)get_player_callback, 99);
  prefab_item(ITEM_MAUL, (Callback)get_player_callback, 99);
  prefab_item(ITEM_DREAMSWORD, (Callback)get_player_callback, 99);
  prefab_item(ITEM_MASTERSWORD, (Callback)get_player_callback, 99);
  prefab_item(ITEM_GODS_WEAPON, (Callback)get_player_callback, 99);
  prefab_item(ITEM_SLINGSHOT, (Callback)get_player_callback, 99);
  prefab_item(ITEM_BIG_SLINGSHOT, (Callback)get_player_callback, 99);
  prefab_item(ITEM_SMALL_THROWING_KNIFE, (Callback)get_player_callback, 99);
  prefab_item(ITEM_SHORTBOW, (Callback)get_player_callback, 99);
  prefab_item(ITEM_THROWING_KNIFE, (Callback)get_player_callback, 99);
  prefab_item(ITEM_LIGHT_CROSSBOW, (Callback)get_player_callback, 99);
  prefab_item(ITEM_HAND_CROSSBOW, (Callback)get_player_callback, 99);
  prefab_item(ITEM_LONGBOW, (Callback)get_player_callback, 99);
  prefab_item(ITEM_HUNTING_BOW, (Callback)get_player_callback, 99);
  prefab_item(ITEM_HEAVY_CROSSBOW, (Callback)get_player_callback, 99);
  prefab_item(ITEM_MASTERBOW, (Callback)get_player_callback, 99);
  prefab_item(ITEM_KILLER_CROSSBOW, (Callback)get_player_callback, 99);
  prefab_item(ITEM_SMALL_STAFF, (Callback)get_player_callback, 99);
  prefab_item(ITEM_STAFF, (Callback)get_player_callback, 99);
  prefab_item(ITEM_BIG_STAFF, (Callback)get_player_callback, 99);
  prefab_item(ITEM_SMALL_SACRED_STAFF, (Callback)get_player_callback, 99);
  prefab_item(ITEM_SACRED_STAFF, (Callback)get_player_callback, 99);
  prefab_item(ITEM_ESSENCED_STAFF, (Callback)get_player_callback, 99);
  prefab_item(ITEM_BLESSED_TRUNK, (Callback)get_player_callback, 99);
  prefab_item(ITEM_EDEN_WOOD, (Callback)get_player_callback, 99);
  prefab_item(ITEM_DARKNESS_CANE, (Callback)get_player_callback, 99);
  prefab_item(ITEM_SPIRITS_GUIDANCE, (Callback)get_player_callback, 99);
  prefab_item(ITEM_ROCK, (Callback)get_player_callback, 99);
  prefab_item(ITEM_SMALL_ARROW, (Callback)get_player_callback, 99);
  prefab_item(ITEM_ARROW, (Callback)get_player_callback, 99);
  prefab_item(ITEM_LARGE_ARROW, (Callback)get_player_callback, 99);
  prefab_item(ITEM_WOOD_SHIELD, (Callback)get_player_callback, 99);
  prefab_item(ITEM_SMALL_METAL_SHIELD, (Callback)get_player_callback, 99);
  prefab_item(ITEM_METAL_SHIELD, (Callback)get_player_callback, 99);
  prefab_item(ITEM_STRONG_METAL_SHIELD, (Callback)get_player_callback, 99);
  prefab_item(ITEM_TITANIUM_SHIELD, (Callback)get_player_callback, 99);
  prefab_item(ITEM_LIGHT_ARMOUR, (Callback)get_player_callback, 99);
  prefab_item(ITEM_WEAK_METAL_ARMOUR, (Callback)get_player_callback, 99);
  prefab_item(ITEM_METAL_ARMOUR, (Callback)get_player_callback, 99);
  prefab_item(ITEM_STRONG_METAL_ARMOUR, (Callback)get_player_callback, 99);
  prefab_item(ITEM_TITANIUM_ARMOUR, (Callback)get_player_callback, 99);
  prefab_item(ITEM_SLIME_FLUID, (Callback)get_player_callback, 99);
  prefab_item(ITEM_SACRED_WOOD, (Callback)get_player_callback, 99);
  prefab_item(ITEM_UNDEAD_MEAT, (Callback)get_player_callback, 99);
  prefab_item(ITEM_SKULLWALKER_BONE, (Callback)get_player_callback, 99);
  prefab_item(ITEM_HOLY_WATER, (Callback)get_player_callback, 99);
  prefab_item(ITEM_ANIMAL_BLOOD, (Callback)get_player_callback, 99);
  prefab_item(ITEM_HUMAN_BLOOD, (Callback)get_player_callback, 99);
  prefab_item(ITEM_ANIMAL_ORGAN, (Callback)get_player_callback, 99);
  prefab_item(ITEM_HUMAN_ORGAN, (Callback)get_player_callback, 99);
  prefab_item(ITEM_LOCKPICK, (Callback)get_player_callback, 99);
  prefab_item(ITEM_ADVANCED_LOCKPICK, (Callback)get_player_callback, 99);
  prefab_item(ITEM_MAGICAL_LOCKPICK, (Callback)get_player_callback, 99);
  prefab_item(ITEM_HEALING_POTION, (Callback)get_player_callback, 99);
  prefab_item(ITEM_LARGE_HEALING_POTION, (Callback)get_player_callback, 99);
  prefab_item(ITEM_GREAT_HEALING_POTION, (Callback)get_player_callback, 99);
  prefab_item(ITEM_WILL_POTION, (Callback)get_player_callback, 99);
  prefab_item(ITEM_LARGE_WILL_POTION, (Callback)get_player_callback, 99);
  prefab_item(ITEM_GREAT_WILL_POTION, (Callback)get_player_callback, 99);
  prefab_pause();
}

void
scene_overworld_on_pre_systems(void) {
  global.menu.cursor_id_prv = global.menu.cursor_id;
  global.game.menu_type_prv = global.game.menu_type;
  if (global.game.menu_type == IGM_INVENTORY) {
    if (global.game.fixed_items_order) {
      global.game.rearranged_item = false;
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

#define BLANK_CHAR_STR "\x80\x80\x80"

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
    renderer_text(V2F(UI_RIGHT - 1.625f, y - PX_TO_UNIT), 1, false, false, 0xff5500ff, 1, "\x85");
    renderer_text(V2F(UI_RIGHT - 1.625f, y), 1, false, false, 0xffffaaff, 1, "\x85");
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
      case ITEM_TYPE_SHIELD:
        page = "Shield";
        break;
      case ITEM_TYPE_ARMOUR:
        page = "Armour";
        break;
      case ITEM_TYPE_LOCKPICK:
        page = "Lockpick & Keys";
        break;
      case ITEM_TYPE_POTION:
        page = "Potion";
        break;
      case ITEM_TYPE_MAGIC_COMPONENT:
        page = "Magic Component";
        break;
      case ITEM_TYPE_AMOUNT: break;
    }
    u32 space_amount = (sinf(global.all.time * 10) + 1) * 1.5 + 1;
    renderer_text(V2F(UI_LEFT + (UI_W - 2.0f) * 0.5f, y - PX_TO_UNIT), 1, true, false, 0xff5500ff, 1, "<-%.*s%s%.*s->", space_amount, BLANK_CHAR_STR, page, space_amount, BLANK_CHAR_STR);
    renderer_text(V2F(UI_LEFT + (UI_W - 2.0f) * 0.5f, y), 1, true, false, 0xffffaaff, 1, "<-%.*s%s%.*s->", space_amount, BLANK_CHAR_STR, page, space_amount, BLANK_CHAR_STR);
  }
}
