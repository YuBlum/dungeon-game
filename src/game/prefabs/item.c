#include "engine/ecs.h"
#include "engine/types.h"
#include "game/components.h"
#include <string.h>

static void
setup_item(Item *item, const char *name, ItemType type, u32 weight, u32 id) {
#if 0
  const char *name = 0;
  switch (type) {
    case ITEM_WOOD_SWORD:
      name = "Wood Sword";
      break;
    case ITEM_KNIFE:
      name = "Knife";
      break;
    case ITEM_DAGGER:
      name = "Dagger";
      break;
    case ITEM_SHORTSWORD:
      name = "Shortsword";
      break;
    case ITEM_HANDAXE:
      name = "Handaxe";
      break;
    case ITEM_LONGSWORD:
      name = "Longsword";
      break;
    case ITEM_TRIDANT:
      name = "Tridant";
      break;
    case ITEM_WARHAMMER:
      name = "Warhammer";
      break;
    case ITEM_GREATSWORD:
      name = "Greatsword";
      break;
    case ITEM_BATTLEAXE:
      name = "Battleaxe";
      break;
    case ITEM_MAUL:
      name = "Maul";
      break;
    case ITEM_DREAMSWORD:
      name = "Dreamsword";
      break;
    case ITEM_MASTERSWORD:
      name = "Mastersword";
      break;
    case ITEM_GODS_WEAPON:
      name = "God's Weapon";
      break;
    case ITEM_SLINGSHOT:
      name = "Slingshot";
      break;
    case ITEM_BIG_SLINGSHOT:
      name = "Big slingshot";
      break;
    case ITEM_MINI_THROWING_KNIFE:
      name = "Mini Throwing Knife";
      break;
    case ITEM_SHORTBOW:
      name = "Shortbow";
      break;
    case ITEM_THROWING_KNIFE:
      name = "Thorwing Knife";
      break;
    case ITEM_LIGHT_CROSSBOW:
      name = "Light Crossbow";
      break;
    case ITEM_HAND_CROSSBOW:
      name = "Hand Crossbow";
      break;
    case ITEM_LONGBOW:
      name = "Longbow";
      break;
    case ITEM_HUNTING_BOW:
      name = "Hunting Bow";
      break;
    case ITEM_HEAVY_CROSSBOW:
      name = "Heavy Crossbow";
      break;
    case ITEM_MASTERBOW:
      name = "Masterbow";
      break;
    case ITEM_KILLER_CROSSBOW:
      name = "Killer Crossbow";
      break;
    case ITEM_MINI_STAFF:
      name = "Mini Staff";
      break;
    case ITEM_STAFF:
      name = "Staff";
      break;
    case ITEM_BIG_STAFF:
      name = "Big Staff";
      break;
    case ITEM_MINI_SACRED_STAFF:
      name = "Mini Sacred Staff";
      break;
    case ITEM_SACRED_STAFF:
      name = "Sacred Staff";
      break;
    case ITEM_ESSENCED_STAFF:
      name = "Essenced Staff";
      break;
    case ITEM_BLESSED_TRUNK:
      name = "Blessed Trunk";
      break;
    case ITEM_EDEN_WOOD:
      name = "Eden Wood";
      break;
    case ITEM_DARKNESS_CANE:
      name = "Darkness Cane";
      break;
    case ITEM_SPIRITS_GUIDANCE:
      name = "Spirits Guidance";
      break;
    case ITEM_ROCK:
      name = "Rock";
      break;
    case ITEM_SMALL_ARROW:
      name = "Small Arrow";
      break;
    case ITEM_ARROW:
      name = "Arrow";
      break;
    case ITEM_LARGE_ARROW:
      name = "Large Arrow";
      break;
    case ITEM_WOOD_SHIELD:
      name = "Wood Shield";
      break;
    case ITEM_MINI_METAL_SHIELD:
      name = "Mini Metal Shield";
      break;
    case ITEM_METAL_SHIELD:
      name = "Metal Shield";
      break;
    case ITEM_STRONG_METAL_SHIELD:
      name = "Strong Metal Shield";
      break;
    case ITEM_TITANIUM_SHIELD:
      name = "Titanium Shield";
      break;
    case ITEM_LIGHT_ARMOUR:
      name = "Light Armour";
      break;
    case ITEM_WEAK_METAL_ARMOUR:
      name = "Weak Metal Armour";
      break;
    case ITEM_METAL_ARMOUR:
      name = "Metal Armour";
      break;
    case ITEM_STRONG_METAL_ARMOUR:
      name = "Strong Metal Armour";
      break;
    case ITEM_TITANIUM_ARMOUR:
      name = "Titanium Armour";
      break;
    case ITEM_SLIME_FLUID:
      name = "Slime Fluid";
      break;
    case ITEM_SACRED_WOOD:
      name = "Sacred Wood";
      break;
    case ITEM_UNDEAD_MEAT:
      name = "Undead Meat";
      break;
    case ITEM_SKULLWALKER_BONE:
      name = "Skullwalker Bone";
      break;
    case ITEM_HOLY_WATER:
      name = "Holy Water";
      break;
    case ITEM_ANIMAL_BLOOD:
      name = "Animal Blood";
      break;
    case ITEM_HUMAN_BLOOD:
      name = "Human Blood";
      break;
    case ITEM_ANIMAL_ORGAN:
      name = "Animal Organ";
      break;
    case ITEM_HUMAN_ORGAN:
      name = "Human Organ";
      break;
    case ITEM_LOCKPICK:
      name = "Lockpick";
      break;
    case ITEM_ADVANCED_LOCKPICK:
      name = "Advanced Lockpick";
      break;
    case ITEM_MAGICAL_LOCKPICK:
      name = "Magical Lockpick";
      break;
    case ITEM_HEALING_POTION:
      name = "Healing Potion";
      break;
    case ITEM_LARGE_HEALING_POTION:
      name = "Large Healing Potion";
      break;
    case ITEM_GREAT_HEALING_POTION:
      name = "Great Healing Potion";
      break;
    case ITEM_WILL_POTION:
      name = "Will Potion";
      break;
    case ITEM_LARGE_WILL_POTION:
      name = "Large Will Potion";
      break;
    case ITEM_GREAT_WILL_POTION:
      name = "Great Will Potion";
      break;
  }
#endif
  item->weight = weight;
  item->id = id;
  item->name_size = strlen(name);
  item->type = type;
  memcpy(item->name_buff, name, item->name_size);
}

void
prefab_item_melee(const char *name, u32 weight, u32 id, u32 cursor_id, bool equiped, u32 dice_amount, u32 dice_faces, u32 test_modifier, u32 critical_hit, u32 attribute_threshold) {
  DiceTest dice_test = {
    dice_amount,
    dice_faces,
    test_modifier
  };
  Item item;
  setup_item(&item, name, ITEM_MELEE, weight, id);
  ecs_entity_creation_begin("item", "active", "cursor-id", "dice-test", "critical-hit", "attribute-threshold", "item-equiped");
    ecs_entity_creation_setup_component(Item, "item", item);
    ecs_entity_creation_setup_component(u32, "cursor-id", cursor_id);
    ecs_entity_creation_setup_component(DiceTest, "dice-test", dice_test);
    ecs_entity_creation_setup_component(u32, "critical-hit", critical_hit);
    ecs_entity_creation_setup_component(u32, "attribute-threshold", attribute_threshold);
    ecs_entity_creation_setup_component(bool, "item-equiped", equiped);
    ecs_entity_creation_setup_component(bool, "active", false);
  ecs_entity_creation_end();
}

void
prefab_item_ranged(const char *name, u32 weight, u32 id, u32 cursor_id, bool equiped, u32 dice_amount, u32 dice_faces, u32 test_modifier, u32 critical_hit, u32 attribute_threshold, AmmoType ammo_type) {
  DiceTest dice_test = {
    dice_amount,
    dice_faces,
    test_modifier
  };
  Item item;
  setup_item(&item, name, ITEM_RANGED, weight, id);
  ecs_entity_creation_begin("item", "active", "cursor-id", "dice-test", "critical-hit", "ammo-type", "attribute-threshold", "item-equiped");
    ecs_entity_creation_setup_component(Item, "item", item);
    ecs_entity_creation_setup_component(u32, "cursor-id", cursor_id);
    ecs_entity_creation_setup_component(DiceTest, "dice-test", dice_test);
    ecs_entity_creation_setup_component(u32, "critical-hit", critical_hit);
    ecs_entity_creation_setup_component(AmmoType, "ammo-type", ammo_type);
    ecs_entity_creation_setup_component(u32, "attribute-threshold", attribute_threshold);
    ecs_entity_creation_setup_component(bool, "item-equiped", equiped);
    ecs_entity_creation_setup_component(bool, "active", false);
  ecs_entity_creation_end();
}

void
prefab_item_staff(const char *name, u32 weight, u32 id, u32 cursor_id, bool equiped, SpellType spell_type, u32 reduce_spell_dt, u32 attribute_threshold) {
  Staff staff = {
    spell_type,
    reduce_spell_dt
  };
  Item item;
  setup_item(&item, name, ITEM_MELEE, weight, id);
  ecs_entity_creation_begin("item", "active", "cursor-id", "staff", "attribute-threshold", "item-equiped");
    ecs_entity_creation_setup_component(Item, "item", item);
    ecs_entity_creation_setup_component(u32, "cursor-id", cursor_id);
    ecs_entity_creation_setup_component(Staff, "staff", staff);
    ecs_entity_creation_setup_component(u32, "attribute-threshold", attribute_threshold);
    ecs_entity_creation_setup_component(bool, "item-equiped", equiped);
    ecs_entity_creation_setup_component(bool, "active", false);
  ecs_entity_creation_end();
}

void
prefab_item_ammo(const char *name, u32 weight, u32 id, u32 cursor_id, AmmoType ammo_type, u32 amount) {
  Item item;
  setup_item(&item, name, ITEM_RANGED, weight, id);
  ecs_entity_creation_begin("item", "active", "cursor-id", "ammo-type", "item-amount");
    ecs_entity_creation_setup_component(Item, "item", item);
    ecs_entity_creation_setup_component(u32, "cursor-id", cursor_id);
    ecs_entity_creation_setup_component(AmmoType, "ammo-type", ammo_type);
    ecs_entity_creation_setup_component(u32, "item-amount", amount);
    ecs_entity_creation_setup_component(bool, "active", false);
  ecs_entity_creation_end();
}

void
prefab_item_defensive(const char *name, u32 weight, u32 id, u32 cursor_id, bool equiped, u32 attribute_threshold, DefensiveType defensive_type, u32 extra_armour_points) {
  DefensiveItem defensive_item = {
    defensive_type,
    extra_armour_points
  };
  Item item;
  setup_item(&item, name, ITEM_MELEE, weight, id);
  ecs_entity_creation_begin("item", "active", "cursor-id", "attribute-threshold", "item-equiped", "defensive-item");
    ecs_entity_creation_setup_component(Item, "item", item);
    ecs_entity_creation_setup_component(u32, "cursor-id", cursor_id);
    ecs_entity_creation_setup_component(u32, "attribute-threshold", attribute_threshold);
    ecs_entity_creation_setup_component(bool, "item-equiped", equiped);
    ecs_entity_creation_setup_component(DefensiveItem, "defensive-item", defensive_item);
    ecs_entity_creation_setup_component(bool, "active", false);
  ecs_entity_creation_end();
}

void
prefab_item_lockpick(const char *name, u32 weight, u32 id, u32 cursor_id, LockpickType lockpick_type, u32 amount) {
  Item item;
  setup_item(&item, name, ITEM_RANGED, weight, id);
  ecs_entity_creation_begin("item", "active", "cursor-id", "lockpick-type", "item-amount");
    ecs_entity_creation_setup_component(Item, "item", item);
    ecs_entity_creation_setup_component(u32, "cursor-id", cursor_id);
    ecs_entity_creation_setup_component(LockpickType, "lockpick-type", lockpick_type);
    ecs_entity_creation_setup_component(u32, "item-amount", amount);
    ecs_entity_creation_setup_component(bool, "active", false);
  ecs_entity_creation_end();
}

void
prefab_item_potion(const char *name, u32 weight, u32 id, u32 cursor_id, u32 dice_amount, u32 dice_faces, u32 test_modifier, PotionType potion_type, u32 amount) {
  DiceTest dice_test = {
    dice_amount,
    dice_faces,
    test_modifier
  };
  Item item;
  setup_item(&item, name, ITEM_RANGED, weight, id);
  ecs_entity_creation_begin("item", "active", "cursor-id", "potion-type", "dice-test", "item-amount");
    ecs_entity_creation_setup_component(Item, "item", item);
    ecs_entity_creation_setup_component(u32, "cursor-id", cursor_id);
    ecs_entity_creation_setup_component(PotionType, "potion-type", potion_type);
    ecs_entity_creation_setup_component(DiceTest, "dice-test", dice_test);
    ecs_entity_creation_setup_component(u32, "item-amount", amount);
    ecs_entity_creation_setup_component(bool, "active", false);
  ecs_entity_creation_end();
}
