#include "engine/ecs.h"
#include "engine/types.h"
#include "game/components.h"
#include "general/global.h"
#include <string.h>

static void
setup_item(ItemInfo *item, const char *name, ItemType type, u32 weight) {
  item->weight = weight;
  item->id = global.game.items_amount++;
  item->name_size = strlen(name);
  item->type = type;
  memcpy(item->name_buff, name, item->name_size);
}

static void
prefab_item_melee(const char *name, u32 weight, u32 dice_amount, u32 dice_faces, u32 test_modifier, u32 critical_hit, u32 attribute_threshold) {
  DiceTest dice_test = {
    dice_amount,
    dice_faces,
    test_modifier
  };
  ItemInfo item;
  setup_item(&item, name, ITEM_TYPE_MELEE, weight);
  ecs_entity_creation_begin("item-info", "active", "dice-test", "critical-hit", "attribute-threshold", "item-equiped");
    ecs_entity_creation_setup_component(ItemInfo, "item-info", item);
    ecs_entity_creation_setup_component(DiceTest, "dice-test", dice_test);
    ecs_entity_creation_setup_component(u32, "critical-hit", critical_hit);
    ecs_entity_creation_setup_component(u32, "attribute-threshold", attribute_threshold);
    ecs_entity_creation_setup_component(bool, "item-equiped", false);
    ecs_entity_creation_setup_component(bool, "active", false);
  ecs_entity_creation_end();
}

static void
prefab_item_ranged(const char *name, u32 weight, u32 dice_amount, u32 dice_faces, u32 test_modifier, u32 critical_hit, u32 attribute_threshold, AmmoType ammo_type) {
  DiceTest dice_test = {
    dice_amount,
    dice_faces,
    test_modifier
  };
  ItemInfo item;
  setup_item(&item, name, ITEM_TYPE_RANGED, weight);
  ecs_entity_creation_begin("item-info", "active", "dice-test", "critical-hit", "ammo-type", "attribute-threshold", "item-equiped");
    ecs_entity_creation_setup_component(ItemInfo, "item-info", item);
    ecs_entity_creation_setup_component(DiceTest, "dice-test", dice_test);
    ecs_entity_creation_setup_component(u32, "critical-hit", critical_hit);
    ecs_entity_creation_setup_component(AmmoType, "ammo-type", ammo_type);
    ecs_entity_creation_setup_component(u32, "attribute-threshold", attribute_threshold);
    ecs_entity_creation_setup_component(bool, "item-equiped", false);
    ecs_entity_creation_setup_component(bool, "active", false);
  ecs_entity_creation_end();
}

static void
prefab_item_staff(const char *name, u32 weight, SpellType spell_type, u32 reduce_spell_dt, u32 attribute_threshold) {
  Staff staff = {
    spell_type,
    reduce_spell_dt
  };
  ItemInfo item;
  setup_item(&item, name, ITEM_TYPE_MELEE, weight);
  ecs_entity_creation_begin("item-info", "active", "staff", "attribute-threshold", "item-equiped");
    ecs_entity_creation_setup_component(ItemInfo, "item-info", item);
    ecs_entity_creation_setup_component(Staff, "staff", staff);
    ecs_entity_creation_setup_component(u32, "attribute-threshold", attribute_threshold);
    ecs_entity_creation_setup_component(bool, "item-equiped", false);
    ecs_entity_creation_setup_component(bool, "active", false);
  ecs_entity_creation_end();
}

static void
prefab_item_ammo(const char *name, u32 weight, AmmoType ammo_type, u32 amount) {
  ItemInfo item;
  setup_item(&item, name, ITEM_TYPE_RANGED, weight);
  ecs_entity_creation_begin("item-info", "active", "ammo-type", "item-amount");
    ecs_entity_creation_setup_component(ItemInfo, "item-info", item);
    ecs_entity_creation_setup_component(AmmoType, "ammo-type", ammo_type);
    ecs_entity_creation_setup_component(u32, "item-amount", amount);
    ecs_entity_creation_setup_component(bool, "active", false);
  ecs_entity_creation_end();
}

static void
prefab_item_defensive(const char *name, u32 weight, u32 attribute_threshold, DefensiveType defensive_type, u32 extra_armour_points) {
  DefensiveItem defensive_item = {
    defensive_type,
    extra_armour_points
  };
  ItemInfo item;
  setup_item(&item, name, ITEM_TYPE_MELEE, weight);
  ecs_entity_creation_begin("item-info", "active", "attribute-threshold", "item-equiped", "defensive-item");
    ecs_entity_creation_setup_component(ItemInfo, "item-info", item);
    ecs_entity_creation_setup_component(u32, "attribute-threshold", attribute_threshold);
    ecs_entity_creation_setup_component(bool, "item-equiped", false);
    ecs_entity_creation_setup_component(DefensiveItem, "defensive-item", defensive_item);
    ecs_entity_creation_setup_component(bool, "active", false);
  ecs_entity_creation_end();
}

static void
prefab_item_lockpick(const char *name, u32 weight, LockpickType lockpick_type, u32 amount) {
  ItemInfo item;
  setup_item(&item, name, ITEM_TYPE_RANGED, weight);
  ecs_entity_creation_begin("item-info", "active", "lockpick-type", "item-amount");
    ecs_entity_creation_setup_component(ItemInfo, "item-info", item);
    ecs_entity_creation_setup_component(LockpickType, "lockpick-type", lockpick_type);
    ecs_entity_creation_setup_component(u32, "item-amount", amount);
    ecs_entity_creation_setup_component(bool, "active", false);
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
  setup_item(&item, name, ITEM_TYPE_RANGED, weight);
  ecs_entity_creation_begin("item-info", "active", "potion-type", "dice-test", "item-amount");
    ecs_entity_creation_setup_component(ItemInfo, "item-info", item);
    ecs_entity_creation_setup_component(PotionType, "potion-type", potion_type);
    ecs_entity_creation_setup_component(DiceTest, "dice-test", dice_test);
    ecs_entity_creation_setup_component(u32, "item-amount", amount);
    ecs_entity_creation_setup_component(bool, "active", false);
  ecs_entity_creation_end();
}

static void
prefab_item_magic_component(const char *name, u32 weight, MagicComponentType magic_component_type, u32 amount) {
  ItemInfo item;
  setup_item(&item, name, ITEM_TYPE_RANGED, weight);
  ecs_entity_creation_begin("item-info", "active", "magic-component-type", "item-amount");
    ecs_entity_creation_setup_component(ItemInfo, "item-info", item);
    ecs_entity_creation_setup_component(MagicComponentType, "magic-component-type", magic_component_type);
    ecs_entity_creation_setup_component(u32, "item-amount", amount);
    ecs_entity_creation_setup_component(bool, "active", false);
  ecs_entity_creation_end();
}

void
prefab_item(Item item, u32 amount) {
  switch (item) {
    case ITEM_WOOD_SWORD:
      prefab_item_melee("Wood Sword", 4, 1, 4, 0, 18, 0); 
      break;
    case ITEM_KNIFE:
      prefab_item_melee("Knife", 2, 1, 6, 0, 18, 1); 
      break;
    case ITEM_DAGGER:
      prefab_item_melee("Dagger", 2, 1, 6, 0, 16, 1); 
      break;
    case ITEM_SHORTSWORD:
      prefab_item_melee("Shortsword", 6, 1, 8, 0, 18, 2); 
      break;
    case ITEM_HANDAXE:
      prefab_item_melee("Handaxe", 10, 1, 8, 0, 16, 2); 
      break;
    case ITEM_LONGSWORD:
      prefab_item_melee("Longsword", 14, 2, 4, 0, 18, 3);
      break;
    case ITEM_TRIDANT:
      prefab_item_melee("Tridant", 14, 2, 4, 0, 16, 3);
      break;
    case ITEM_WARHAMMER:
      prefab_item_melee("Warhammer", 20, 1, 12, 0, 18, 3);
      break;
    case ITEM_GREATSWORD:
      prefab_item_melee("GreatSword", 24, 2, 6, 0, 18, 3);
      break;
    case ITEM_BATTLEAXE:
      prefab_item_melee("Battleaxe", 28, 1, 12, 0, 16, 4);
      break;
    case ITEM_MAUL:
      prefab_item_melee("Maul", 32, 3, 4, 0, 16, 4);
      break;
    case ITEM_DREAMSWORD:
      prefab_item_melee("Dreamsword", 36, 2, 12, 0, 18, 4);
      break;
    case ITEM_MASTERSWORD:
      prefab_item_melee("Mastersword", 36, 2, 12, 0, 16, 5);
      break;
    case ITEM_GODS_WEAPON:
      prefab_item_melee("God's Spear", 40, 3, 12, 0, 16, 5);
      break;
    case ITEM_SLINGSHOT:
      prefab_item_ranged("Slingshot", 2, 1, 4, 0, 18, 0, AMMO_ROCK);
      break;
    case ITEM_BIG_SLINGSHOT:
      prefab_item_ranged("Big Slingshot", 2, 1, 4, 0, 16, 0, AMMO_ROCK);
      break;
    case ITEM_MINI_THROWING_KNIFE:
      prefab_item_ranged("Mini Throwing-Knife", 4, 1, 6, 0, 18, 0, AMMO_NONE);
      break;
    case ITEM_SHORTBOW:
      prefab_item_ranged("Shortbow", 8, 1,  6, 0, 16, 0, AMMO_SMALL_ARROW);
      break;
    case ITEM_THROWING_KNIFE:
      prefab_item_ranged("Throwing-Knife", 6, 1, 8, 0, 16, 0, AMMO_NONE);
      break;
    case ITEM_LIGHT_CROSSBOW:
      prefab_item_ranged("Light Crossbow", 16, 1, 8, 0, 16, 0, AMMO_SMALL_ARROW);
      break;
    case ITEM_HAND_CROSSBOW:
      prefab_item_ranged("Hand Crossbow", 26, 2, 4, 0, 18, 0, AMMO_ARROW);
      break;
    case ITEM_LONGBOW:
      prefab_item_ranged("Longbow", 36, 1, 10, 0, 18, 0, AMMO_ARROW);
      break;
    case ITEM_HUNTING_BOW:
      prefab_item_ranged("Hunting Bow", 34, 1, 10, 0, 16, 0, AMMO_ARROW);
      break;
    case ITEM_HEAVY_CROSSBOW:
      prefab_item_ranged("Heavy Crossbow", 50, 2, 4, 2, 18, 0, AMMO_LARGE_ARROW);
      break;
    case ITEM_MASTERBOW:
      prefab_item_ranged("Masterbow", 45, 2,  6, 2, 16, 0, AMMO_LARGE_ARROW);
      break;
    case ITEM_KILLER_CROSSBOW:
      prefab_item_ranged("Killer Crossbow", 58, 2, 8, 0, 16, 0, AMMO_LARGE_ARROW);
      break;
    case ITEM_MINI_STAFF:
      prefab_item_staff("Mini Staff", 2, SPELL_REGULAR, 0, 0);
      break;
    case ITEM_STAFF:
       prefab_item_staff("Staff", 4, SPELL_REGULAR, 1, 0);
      break;
    case ITEM_BIG_STAFF:
         prefab_item_staff("Big Staff", 6, SPELL_REGULAR, 2, 1);
      break;
    case ITEM_MINI_SACRED_STAFF:
         prefab_item_staff("Mini Sacred Staff", 4, SPELL_COMPLEX, 0, 1);
      break;
    case ITEM_SACRED_STAFF:
         prefab_item_staff("Sacred Staff", 6, SPELL_COMPLEX, 1, 2);
      break;
    case ITEM_ESSENCED_STAFF:
         prefab_item_staff("Essenced Staff", 6, SPELL_COMPLEX, 2, 2);
      break;
    case ITEM_BLESSED_TRUNK:
         prefab_item_staff("Blessed Trunk", 8, SPELL_EXTREME, 0, 3);
      break;
    case ITEM_EDEN_WOOD:
         prefab_item_staff("Eden Wood", 8, SPELL_EXTREME, 1, 3);
      break;
    case ITEM_DARKNESS_CANE:
         prefab_item_staff("Darkness Cane", 8, SPELL_EXTREME, 2, 4);
      break;
    case ITEM_SPIRITS_GUIDANCE:
         prefab_item_staff("Spirits Guidance", 10, SPELL_COMPLEX, 3, 4);
      break;
    case ITEM_ROCK:
      prefab_item_ammo("Rock", 1, AMMO_ROCK, amount);
      break;
    case ITEM_SMALL_ARROW:
      prefab_item_ammo("Small Arrow", 6, AMMO_SMALL_ARROW, amount);
      break;
    case ITEM_ARROW:
      prefab_item_ammo("Arrow", 8, AMMO_ARROW, 1);
      break;
    case ITEM_LARGE_ARROW:
      prefab_item_ammo("Large Arrow", 12, AMMO_ARROW, 1);
      break;
    case ITEM_WOOD_SHIELD:
      prefab_item_defensive("Wood Shield", 6, 0, DEF_SHIELD, 1);
      break;
    case ITEM_MINI_METAL_SHIELD:
      prefab_item_defensive("Mini Metal Shield", 12, 2, DEF_SHIELD, 2);
      break;
    case ITEM_METAL_SHIELD:
      prefab_item_defensive("Metal Shield", 18, 3, DEF_SHIELD, 3);
      break;
    case ITEM_STRONG_METAL_SHIELD:
      prefab_item_defensive("Strong Metal Shield", 24, 4, DEF_SHIELD, 4);
      break;
    case ITEM_TITANIUM_SHIELD:
      prefab_item_defensive("Titanium Shield", 36, 5, DEF_SHIELD, 5);
      break;
    case ITEM_LIGHT_ARMOUR:
      prefab_item_defensive("Light Armour", 8, 1, DEF_ARMOUR, 1);
      break;
    case ITEM_WEAK_METAL_ARMOUR:
      prefab_item_defensive("Weak Metal Armour", 12, 2, DEF_ARMOUR, 2);
      break;
    case ITEM_METAL_ARMOUR:
      prefab_item_defensive("Metal Armour", 16, 3, DEF_ARMOUR, 3);
      break;
    case ITEM_STRONG_METAL_ARMOUR:
      prefab_item_defensive("Strong Metal Armour", 24, 4, DEF_ARMOUR, 4);
      break;
    case ITEM_TITANIUM_ARMOUR:
      prefab_item_defensive("Titanium Armour", 26, 5, DEF_ARMOUR, 5);
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
      prefab_item_potion("Healing Potion", 1, 1, 4, 0, POTION_HEALING, amount);
      break;
    case ITEM_LARGE_HEALING_POTION:
      prefab_item_potion("Large Healing Potion", 2, 2, 4, 0, POTION_HEALING, amount);
      break;
    case ITEM_GREAT_HEALING_POTION:
      prefab_item_potion("Great Healing Potion", 4, 3, 4, 0, POTION_HEALING, amount);
      break;
    case ITEM_WILL_POTION:
      prefab_item_potion("Will Potion", 1, 1, 4, 0, POTION_WILL, amount);
      break;
    case ITEM_LARGE_WILL_POTION:
      prefab_item_potion("Large Will Potion", 2, 2, 4, 0, POTION_WILL, amount);
      break;
    case ITEM_GREAT_WILL_POTION:
      prefab_item_potion("Great Will Potion", 4, 3, 4, 0, POTION_WILL, amount);
      break;
  }
}
