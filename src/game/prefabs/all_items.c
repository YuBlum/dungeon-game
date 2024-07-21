#include "engine/types.h"
#include "general/global.h"
#include "game/prefabs.h"

void
prefab_all_items(void) {
  global.game.items_cursor_id = 1;
  u32 item_id = 0;

  prefab_item_melee("Wood Sword",   4, item_id++, false, 1,  4, 0, 18, 0); 
  prefab_item_melee("Knife",        2, item_id++, false, 1,  6, 0, 18, 1); 
  prefab_item_melee("Dagger",       2, item_id++, false, 1,  6, 0, 16, 1); 
  prefab_item_melee("Shortsword",   6, item_id++, false, 1,  8, 0, 18, 2); 
  prefab_item_melee("Handaxe",     10, item_id++, false, 1,  8, 0, 16, 2); 
  prefab_item_melee("Longsword",   14, item_id++, false, 2,  4, 0, 18, 3);
  prefab_item_melee("Tridant",     14, item_id++, false, 2,  4, 0, 16, 3);
  prefab_item_melee("Warhammer",   20, item_id++, false, 1, 12, 0, 18, 3);
  prefab_item_melee("GreatSword",  24, item_id++, false, 2,  6, 0, 18, 3);
  prefab_item_melee("Battleaxe",   28, item_id++, false, 1, 12, 0, 16, 4);
  prefab_item_melee("Maul",        32, item_id++, false, 3,  4, 0, 16, 4);
  prefab_item_melee("Dreamsword",  36, item_id++, false, 2, 12, 0, 18, 4);
  prefab_item_melee("Mastersword", 36, item_id++, false, 2, 12, 0, 16, 5);
  prefab_item_melee("God's Spear", 40, item_id++, false, 3, 12, 0, 16, 5);

  prefab_item_ranged("Slingshot",            2, item_id++, false, 1,  4, 0, 18, 0, AMMO_ROCK);
  prefab_item_ranged("Big Slingshot",        2, item_id++, false, 1,  4, 0, 16, 0, AMMO_ROCK);
  prefab_item_ranged("Mini Throwing-Knife",  4, item_id++, false, 1,  6, 0, 18, 0, AMMO_NONE);
  prefab_item_ranged("Shortbow",             8, item_id++, false, 1,  6, 0, 16, 0, AMMO_SMALL_ARROW);
  prefab_item_ranged("Throwing-Knife",       6, item_id++, false, 1,  8, 0, 16, 0, AMMO_NONE);
  prefab_item_ranged("Light Crossbow",      16, item_id++, false, 1,  8, 0, 16, 0, AMMO_SMALL_ARROW);
  prefab_item_ranged("Hand Crossbow",       26, item_id++, false, 2,  4, 0, 18, 0, AMMO_ARROW);
  prefab_item_ranged("Longbow",             36, item_id++, false, 1, 10, 0, 18, 0, AMMO_ARROW);
  prefab_item_ranged("Hunting Bow",         34, item_id++, false, 1, 10, 0, 16, 0, AMMO_ARROW);
  prefab_item_ranged("Heavy Crossbow",      50, item_id++, false, 2,  4, 2, 18, 0, AMMO_LARGE_ARROW);
  prefab_item_ranged("Masterbow",           45, item_id++, false, 2,  6, 2, 16, 0, AMMO_LARGE_ARROW);
  prefab_item_ranged("Killer Crossbow",     58, item_id++, false, 2,  8, 0, 16, 0, AMMO_LARGE_ARROW);
}
