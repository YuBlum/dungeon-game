#include "engine/ecs.h"
#include "engine/types.h"
#include "game/components.h"

void
prefab_melee_weapon(MeleeWeaponType type, DiceTest dice_test, u32 critical_hit, u32 weight) {
  Tag tag;
  switch (type) {
    case MELEE_WOOD_SWORD:
      tag = "Wood Sword";
      break;
    case MELEE_KNIFE:
      tag = "Knife";
      break;
    case MELEE_DAGGER:
      tag = "Dagger";
      break;
    case MELEE_SHORTSWORD:
      tag = "Shortsword";
      break;
    case MELEE_HANDAXE:
      tag = "Handaxe";
      break;
    case MELEE_LONGSWORD:
      tag = "Longsword";
      break;
    case MELEE_TRIDANT:
      tag = "Tridant";
      break;
    case MELEE_WARHAMMER:
      tag = "Warhammer";
      break;
    case MELEE_GREATSWORD:
      tag = "Greatsword";
      break;
    case MELEE_BATTLEAXE:
      tag = "Battleaxe";
      break;
    case MELEE_MAUL:
      tag = "Maul";
      break;
    case MELEE_DREAMSWORD:
      tag = "Dreamsword";
      break;
    case MELEE_MASTERSWORD:
      tag = "Mastersword";
      break;
    case MELEE_GODS_WEAPON:
      tag = "Gods Weapon";
      break;
  }
  ecs_entity_creation_begin("melee-weapon-type", "tag", "dice-test", "critical-hit", "item-weight");
    ecs_entity_creation_setup_component(MeleeWeaponType, "melee-weapon-type", type);
    ecs_entity_creation_setup_component(Tag, "tag", tag);
    ecs_entity_creation_setup_component(DiceTest, "dice-test", dice_test);
    ecs_entity_creation_setup_component(u32, "critical-hit", critical_hit);
    ecs_entity_creation_setup_component(u32, "item-weight", weight);
  ecs_entity_creation_end();
}
