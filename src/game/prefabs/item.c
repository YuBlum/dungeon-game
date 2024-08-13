#include "engine/ecs.h"
#include "engine/types.h"
#include "game/components.h"
#include "general/global.h"
#include <string.h>

static void
setup_item(ItemInfo *item, const char *name, ItemType type, u32 weight) {
  item->weight = weight;
  item->id = global.game.items_amount[type]++;
  item->name_size = strlen(name);
  item->type = type;
  memcpy(item->name_buff, name, item->name_size);
}

static void
prefab_item_melee(const char *name, Callback get_player, u32 weight, u32 dice_amount, u32 dice_faces, u32 test_modifier, u32 critical_hit, i32 attribute_threshold) {
  DiceTest dice_test = {
    dice_amount,
    dice_faces,
    test_modifier
  };
  ItemInfo item;
  setup_item(&item, name, ITEM_TYPE_MELEE, weight);
  ecs_entity_creation_begin("item-info", "dice-test", "critical-hit", "attribute-threshold", "item-equiped", "item-melee", "callback", "item-weapon");
    ecs_entity_creation_setup_component(ItemInfo, "item-info", item);
    ecs_entity_creation_setup_component(DiceTest, "dice-test", dice_test);
    ecs_entity_creation_setup_component(u32, "critical-hit", critical_hit);
    ecs_entity_creation_setup_component(i32, "attribute-threshold", attribute_threshold);
    ecs_entity_creation_setup_component(bool, "item-equiped", false);
    ecs_entity_creation_setup_component(Callback, "callback", get_player);
  ecs_entity_creation_end();
}

static void
prefab_item_ranged(const char *name, Callback get_player, u32 weight, u32 dice_amount, u32 dice_faces, u32 test_modifier, u32 critical_hit, i32 attribute_threshold, AmmoType ammo_type, u32 amount) {
  DiceTest dice_test = {
    dice_amount,
    dice_faces,
    test_modifier
  };
  ItemInfo item;
  setup_item(&item, name, ITEM_TYPE_RANGED, weight);
  if (amount == 0) {
    ecs_entity_creation_begin("item-info", "dice-test", "critical-hit", "ammo-type", "attribute-threshold", "item-equiped", "item-ranged", "callback", "item-weapon");
  } else {
    ecs_entity_creation_begin("item-info", "dice-test", "critical-hit", "ammo-type", "attribute-threshold", "item-equiped", "item-ranged", "item-amount", "callback", "item-weapon");
      ecs_entity_creation_setup_component(u32, "item-amount", amount);
  }
    ecs_entity_creation_setup_component(ItemInfo, "item-info", item);
    ecs_entity_creation_setup_component(DiceTest, "dice-test", dice_test);
    ecs_entity_creation_setup_component(u32, "critical-hit", critical_hit);
    ecs_entity_creation_setup_component(AmmoType, "ammo-type", ammo_type);
    ecs_entity_creation_setup_component(i32, "attribute-threshold", attribute_threshold);
    ecs_entity_creation_setup_component(bool, "item-equiped", false);
    ecs_entity_creation_setup_component(Callback, "callback", get_player);
  ecs_entity_creation_end();
}

static void
prefab_item_staff(const char *name, Callback get_player, u32 weight, SpellType spell_type, u32 reduce_spell_dt, i32 attribute_threshold) {
  Staff staff = {
    spell_type,
    reduce_spell_dt
  };
  ItemInfo item;
  setup_item(&item, name, ITEM_TYPE_STAFF, weight);
  ecs_entity_creation_begin("item-info", "staff", "attribute-threshold", "item-equiped", "item-staff", "callback", "item-weapon");
    ecs_entity_creation_setup_component(ItemInfo, "item-info", item);
    ecs_entity_creation_setup_component(Staff, "staff", staff);
    ecs_entity_creation_setup_component(i32, "attribute-threshold", attribute_threshold);
    ecs_entity_creation_setup_component(bool, "item-equiped", false);
    ecs_entity_creation_setup_component(Callback, "callback", get_player);
  ecs_entity_creation_end();
}

static void
prefab_item_ammo(const char *name, u32 weight, AmmoType ammo_type, u32 amount) {
  ItemInfo item;
  setup_item(&item, name, ITEM_TYPE_AMMO, weight);
  ecs_entity_creation_begin("item-info", "ammo-type", "item-amount", "item-ammo");
    ecs_entity_creation_setup_component(ItemInfo, "item-info", item);
    ecs_entity_creation_setup_component(AmmoType, "ammo-type", ammo_type);
    ecs_entity_creation_setup_component(u32, "item-amount", amount);
  ecs_entity_creation_end();
}

static void
prefab_item_defensive(const char *name, Callback get_player, u32 weight, i32 attribute_threshold, DefensiveType defensive_type, u32 extra_armour_points) {
  DefensiveItem defensive_item = {
    defensive_type,
    extra_armour_points
  };
  ItemInfo item;
  if (defensive_type == DEF_SHIELD) {
    setup_item(&item, name, ITEM_TYPE_SHIELD, weight);
    ecs_entity_creation_begin("item-info", "attribute-threshold", "item-equiped", "defensive-item", "item-defensive", "callback", "item-shield");
  } else {
    setup_item(&item, name, ITEM_TYPE_ARMOUR, weight);
    ecs_entity_creation_begin("item-info", "attribute-threshold", "item-equiped", "defensive-item", "item-defensive", "callback", "item-armour");
  }
    ecs_entity_creation_setup_component(ItemInfo, "item-info", item);
    ecs_entity_creation_setup_component(i32, "attribute-threshold", attribute_threshold);
    ecs_entity_creation_setup_component(bool, "item-equiped", false);
    ecs_entity_creation_setup_component(DefensiveItem, "defensive-item", defensive_item);
    ecs_entity_creation_setup_component(Callback, "callback", get_player);
  ecs_entity_creation_end();
}

static void
prefab_item_lockpick(const char *name, u32 weight, LockpickType lockpick_type, u32 amount) {
  ItemInfo item;
  setup_item(&item, name, ITEM_TYPE_LOCKPICK, weight);
  ecs_entity_creation_begin("item-info", "lockpick-type", "item-amount", "item-lockpick");
    ecs_entity_creation_setup_component(ItemInfo, "item-info", item);
    ecs_entity_creation_setup_component(LockpickType, "lockpick-type", lockpick_type);
    ecs_entity_creation_setup_component(u32, "item-amount", amount);
  ecs_entity_creation_end();
}

static void
prefab_item_potion(const char *name, u32 weight, u32 dice_amount, u32 dice_faces, u32 test_modifier, PotionType potion_type, u32 amount) {
  DiceTest dice_test = {
    dice_amount,
    dice_faces,
    test_modifier
  };
  ItemInfo item;
  setup_item(&item, name, ITEM_TYPE_POTION, weight);
  ecs_entity_creation_begin("item-info", "potion-type", "dice-test", "item-amount", "item-potion");
    ecs_entity_creation_setup_component(ItemInfo, "item-info", item);
    ecs_entity_creation_setup_component(PotionType, "potion-type", potion_type);
    ecs_entity_creation_setup_component(DiceTest, "dice-test", dice_test);
    ecs_entity_creation_setup_component(u32, "item-amount", amount);
  ecs_entity_creation_end();
}

static void
prefab_item_magic_component(const char *name, u32 weight, MagicComponentType magic_component_type, u32 amount) {
  ItemInfo item;
  setup_item(&item, name, ITEM_TYPE_MAGIC_COMPONENT, weight);
  ecs_entity_creation_begin("item-info", "magic-component-type", "item-amount", "item-magic-component");
    ecs_entity_creation_setup_component(ItemInfo, "item-info", item);
    ecs_entity_creation_setup_component(MagicComponentType, "magic-component-type", magic_component_type);
    ecs_entity_creation_setup_component(u32, "item-amount", amount);
  ecs_entity_creation_end();
}

void
prefab_item(Item item, Callback get_player, u32 amount) {
  switch (item) {
    case ITEM_WOOD_SWORD:
      prefab_item_melee("Wood Sword", get_player, 4, 1, 4, 0, 18, 0); 
      break;
    case ITEM_KNIFE:
      prefab_item_melee("Knife", get_player, 2, 1, 6, 0, 18, 1); 
      break;
    case ITEM_DAGGER:
      prefab_item_melee("Dagger", get_player, 2, 1, 6, 0, 16, 1); 
      break;
    case ITEM_SHORTSWORD:
      prefab_item_melee("Shortsword", get_player, 6, 1, 8, 0, 18, 2); 
      break;
    case ITEM_HANDAXE:
      prefab_item_melee("Handaxe", get_player, 10, 1, 8, 0, 16, 2); 
      break;
    case ITEM_LONGSWORD:
      prefab_item_melee("Longsword", get_player, 14, 2, 4, 0, 18, 3);
      break;
    case ITEM_TRIDANT:
      prefab_item_melee("Tridant", get_player, 14, 2, 4, 0, 16, 3);
      break;
    case ITEM_WARHAMMER:
      prefab_item_melee("Warhammer", get_player, 20, 1, 12, 0, 18, 3);
      break;
    case ITEM_GREATSWORD:
      prefab_item_melee("GreatSword", get_player, 24, 2, 6, 0, 18, 3);
      break;
    case ITEM_BATTLEAXE:
      prefab_item_melee("Battleaxe", get_player, 28, 1, 12, 0, 16, 4);
      break;
    case ITEM_MAUL:
      prefab_item_melee("Maul", get_player, 32, 3, 4, 0, 16, 4);
      break;
    case ITEM_DREAMSWORD:
      prefab_item_melee("Dreamsword", get_player, 36, 2, 12, 0, 18, 4);
      break;
    case ITEM_MASTERSWORD:
      prefab_item_melee("Mastersword", get_player, 36, 2, 12, 0, 16, 5);
      break;
    case ITEM_GODS_WEAPON:
      prefab_item_melee("God's Spear", get_player, 40, 3, 12, 0, 16, 5);
      break;
    case ITEM_SLINGSHOT:
      prefab_item_ranged("Slingshot", get_player, 2, 1, 4, 0, 18, 0, AMMO_ROCK, 0);
      break;
    case ITEM_BIG_SLINGSHOT:
      prefab_item_ranged("Big Slingshot", get_player, 2, 1, 4, 0, 16, 1, AMMO_ROCK, 0);
      break;
    case ITEM_SMALL_THROWING_KNIFE:
      prefab_item_ranged("Small Throwing-Knife", get_player, 4, 1, 6, 0, 18, 1, AMMO_NONE, amount);
      break;
    case ITEM_SHORTBOW:
      prefab_item_ranged("Shortbow", get_player, 8, 1,  6, 0, 16, 2, AMMO_SMALL_ARROW, 0);
      break;
    case ITEM_THROWING_KNIFE:
      prefab_item_ranged("Throwing-Knife", get_player, 6, 1, 8, 0, 16, 2, AMMO_NONE, amount);
      break;
    case ITEM_LIGHT_CROSSBOW:
      prefab_item_ranged("Light Crossbow", get_player, 16, 1, 8, 0, 16, 2, AMMO_SMALL_ARROW, 0);
      break;
    case ITEM_HAND_CROSSBOW:
      prefab_item_ranged("Hand Crossbow", get_player, 26, 2, 4, 0, 18, 3, AMMO_ARROW, 0);
      break;
    case ITEM_LONGBOW:
      prefab_item_ranged("Longbow", get_player, 36, 1, 10, 0, 18, 3, AMMO_ARROW, 0);
      break;
    case ITEM_HUNTING_BOW:
      prefab_item_ranged("Hunting Bow", get_player, 34, 1, 10, 0, 16, 3, AMMO_ARROW, 0);
      break;
    case ITEM_HEAVY_CROSSBOW:
      prefab_item_ranged("Heavy Crossbow", get_player, 50, 2, 4, 2, 18, 4, AMMO_LARGE_ARROW, 0);
      break;
    case ITEM_MASTERBOW:
      prefab_item_ranged("Masterbow", get_player, 45, 2,  6, 2, 16, 4, AMMO_LARGE_ARROW, 0);
      break;
    case ITEM_KILLER_CROSSBOW:
      prefab_item_ranged("Killer Crossbow", get_player, 58, 2, 8, 0, 16, 5, AMMO_LARGE_ARROW, 0);
      break;
    case ITEM_SMALL_STAFF:
      prefab_item_staff("Small Staff", get_player, 2, SPELL_REGULAR, 0, -2);
      break;
    case ITEM_STAFF:
       prefab_item_staff("Staff", get_player, 4, SPELL_REGULAR, 1, 0);
      break;
    case ITEM_BIG_STAFF:
         prefab_item_staff("Big Staff", get_player, 6, SPELL_REGULAR, 2, 1);
      break;
    case ITEM_SMALL_SACRED_STAFF:
         prefab_item_staff("Small Sacred Staff", get_player, 4, SPELL_COMPLEX, 0, 1);
      break;
    case ITEM_SACRED_STAFF:
         prefab_item_staff("Sacred Staff", get_player, 6, SPELL_COMPLEX, 1, 2);
      break;
    case ITEM_ESSENCED_STAFF:
         prefab_item_staff("Essenced Staff", get_player, 6, SPELL_COMPLEX, 2, 2);
      break;
    case ITEM_BLESSED_TRUNK:
         prefab_item_staff("Blessed Trunk", get_player, 8, SPELL_EXTREME, 0, 3);
      break;
    case ITEM_EDEN_WOOD:
         prefab_item_staff("Eden Wood", get_player, 8, SPELL_EXTREME, 1, 3);
      break;
    case ITEM_DARKNESS_CANE:
         prefab_item_staff("Darkness Cane", get_player, 8, SPELL_EXTREME, 2, 4);
      break;
    case ITEM_SPIRITS_GUIDANCE:
         prefab_item_staff("Spirits Guidance", get_player, 10, SPELL_EXTREME, 3, 4);
      break;
    case ITEM_ROCK:
      prefab_item_ammo("Rock", 1, AMMO_ROCK, amount);
      break;
    case ITEM_SMALL_ARROW:
      prefab_item_ammo("Small Arrow", 6, AMMO_SMALL_ARROW, amount);
      break;
    case ITEM_ARROW:
      prefab_item_ammo("Arrow", 8, AMMO_ARROW, amount);
      break;
    case ITEM_LARGE_ARROW:
      prefab_item_ammo("Large Arrow", 12, AMMO_LARGE_ARROW, amount);
      break;
    case ITEM_WOOD_SHIELD:
      prefab_item_defensive("Wood Shield", get_player, 6, 0, DEF_SHIELD, 1);
      break;
    case ITEM_SMALL_METAL_SHIELD:
      prefab_item_defensive("Small Metal Shield", get_player, 12, 2, DEF_SHIELD, 2);
      break;
    case ITEM_METAL_SHIELD:
      prefab_item_defensive("Metal Shield", get_player, 18, 3, DEF_SHIELD, 3);
      break;
    case ITEM_STRONG_METAL_SHIELD:
      prefab_item_defensive("Strong Metal Shield", get_player, 24, 4, DEF_SHIELD, 4);
      break;
    case ITEM_TITANIUM_SHIELD:
      prefab_item_defensive("Titanium Shield", get_player, 36, 5, DEF_SHIELD, 5);
      break;
    case ITEM_LIGHT_ARMOUR:
      prefab_item_defensive("Light Armour", get_player, 8, 1, DEF_ARMOUR, 1);
      break;
    case ITEM_WEAK_METAL_ARMOUR:
      prefab_item_defensive("Weak Metal Armour", get_player, 12, 2, DEF_ARMOUR, 2);
      break;
    case ITEM_METAL_ARMOUR:
      prefab_item_defensive("Metal Armour", get_player, 16, 3, DEF_ARMOUR, 3);
      break;
    case ITEM_STRONG_METAL_ARMOUR:
      prefab_item_defensive("Strong Metal Armour", get_player, 24, 4, DEF_ARMOUR, 4);
      break;
    case ITEM_TITANIUM_ARMOUR:
      prefab_item_defensive("Titanium Armour", get_player, 26, 5, DEF_ARMOUR, 5);
      break;
    case ITEM_SLIME_FLUID:
      prefab_item_magic_component("Slime Fluid", 1, MAGIC_SLIME_FLUID, amount);
      break;
    case ITEM_SACRED_WOOD:
      prefab_item_magic_component("Sacred Wood", 2, MAGIC_SACRED_WOOD, amount);
      break;
    case ITEM_UNDEAD_MEAT:
      prefab_item_magic_component("Undead Meat", 1, MAGIC_UNDEAD_MEAT, amount);
      break;
    case ITEM_SKULLWALKER_BONE:
      prefab_item_magic_component("Skullwalker Bone", 2, MAGIC_SKULLWALKER_BONE, amount);
      break;
    case ITEM_HOLY_WATER:
      prefab_item_magic_component("Holy Water", 1, MAGIC_HOLY_WATER, amount);
      break;
    case ITEM_ANIMAL_BLOOD:
      prefab_item_magic_component("Animal Blood", 1, MAGIC_ANIMAL_BLOOD, amount);
      break;
    case ITEM_HUMAN_BLOOD:
      prefab_item_magic_component("Human Blood", 1, MAGIC_HUMAN_BLOOD, amount);
      break;
    case ITEM_ANIMAL_ORGAN:
      prefab_item_magic_component("Animal Organ", 2, MAGIC_ANIMAL_ORGAN, amount);
      break;
    case ITEM_HUMAN_ORGAN:
      prefab_item_magic_component("Human Organ", 2, MAGIC_HUMAN_ORGAN, amount);
      break;
    case ITEM_LOCKPICK:
      prefab_item_lockpick("Lockpick", 2, LOCKPICK_REGULAR, amount);
      break;
    case ITEM_ADVANCED_LOCKPICK:
      prefab_item_lockpick("Advanced Lockpick", 4, LOCKPICK_ADVANCED, amount);
      break;
    case ITEM_MAGICAL_LOCKPICK:
      prefab_item_lockpick("Magical Lockpick", 4, LOCKPICK_MAGICAL, amount);
      break;
    case ITEM_HEALING_POTION:
      prefab_item_potion("Healing Potion", 1, 1, 4, 2, POTION_HEALING, amount); /* 3 to 6 */
      break;
    case ITEM_LARGE_HEALING_POTION:
      prefab_item_potion("Large Healing Potion", 2, 2, 4, 4, POTION_HEALING, amount); /* 6 to 12 */
      break;
    case ITEM_GREAT_HEALING_POTION:
      prefab_item_potion("Great Healing Potion", 4, 4, 4, 4, POTION_HEALING, amount); /* 8 to 20 */
      break;
    case ITEM_WILL_POTION:
      prefab_item_potion("Will Potion", 1, 1, 4, 2, POTION_WILL, amount);
      break;
    case ITEM_LARGE_WILL_POTION:
      prefab_item_potion("Large Will Potion", 2, 2, 4, 4, POTION_WILL, amount);
      break;
    case ITEM_GREAT_WILL_POTION:
      prefab_item_potion("Great Will Potion", 4, 4, 4, 4, POTION_WILL, amount);
      break;
  }
}
