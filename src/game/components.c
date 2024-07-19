#include "game/components.h"
#include "engine/ecs.h"
#include "engine/math.h"
#include "engine/renderer.h"

void
components_create(void) {
  ecs_component_create(V2f, "position");
  ecs_component_create(V2f, "direction");
  ecs_component_create(PositionLerp, "position-lerp");
  ecs_component_create(f32, "speed");
  ecs_component_create(Color, "color");
  ecs_component_create(bool, "bump");
  ecs_component_create(Attributes, "attributes");
  ecs_component_create(DefensiveStats, "defensive-stats");
  ecs_component_create(CharacterSheet, "character-sheet");
  ecs_component_create(Class, "class");
  ecs_component_create(Callback, "callback");
  ecs_component_create(CallbackArg, "callback-arg");
  ecs_component_create(Tag, "tag");
  ecs_component_create(CharacterName, "character-name");
  ecs_component_create(u32, "option-id");
  ecs_component_create(u32, "cursor-id");
  ecs_component_create(Cursor, "cursor");
  ecs_component_create(bool, "active");
  ecs_component_create(u32, "u32-arg");
  ecs_component_create(i32, "attribute-points");
  ecs_component_create(AttributeType, "attribute-type");
  ecs_component_create(EntityReference *, "reference-ptr");
  ecs_component_create(Terminal, "terminal");
  ecs_component_create(bool, "pause");
  ecs_component_create(InGameMenuType, "in-game-menu-type");
  ecs_component_create(ItemPriceRange, "item-price-range");
  ecs_component_create(AmmoType, "ammo-type");
  ecs_component_create(DiceTest, "dice-test");
  ecs_component_create(u32, "critical-hit");
  ecs_component_create(u32, "item-weight");
  ecs_component_create(u32, "item-amount");
  ecs_component_create(bool, "item-equiped");
  ecs_component_create(Item, "item");
  ecs_component_create(u32, "attribute-threshold");
  ecs_component_create(Staff, "staff");
  ecs_component_create(LockpickType, "lockpick-type");
  ecs_component_create(PotionType, "potion-type");
  ecs_component_create(DefensiveItem, "defensive-item");
  ecs_component_create(MagicComponentType, "magic-component-type");

  ecs_empty_component_create("input");
  ecs_empty_component_create("tile");
  ecs_empty_component_create("total-attribute-points");
  ecs_empty_component_create("menu-hint");
  ecs_empty_component_create("item-melee");
  ecs_empty_component_create("item-ranged");
  ecs_empty_component_create("item-ammo");
  ecs_empty_component_create("item-potion");
  ecs_empty_component_create("item-lockpick");
  ecs_empty_component_create("item-component");
}
