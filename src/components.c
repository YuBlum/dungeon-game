#include "include/components.h"
#include "include/ecs.h"
#include "include/math.h"
#include "include/renderer.h"

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
  ecs_component_create(OptionCallback, "option-callback");
  ecs_component_create(OptionCallbackArg, "option-callback-arg");
  ecs_component_create(Tag, "tag");
  ecs_component_create(CharacterName, "character-name");
  ecs_component_create(u32, "option-id");
  ecs_component_create(u32, "cursor-id");
  ecs_component_create(Cursor, "cursor");
  ecs_component_create(bool, "active");
  ecs_component_create(u32, "u32-arg");
  ecs_component_create(i32, "attribute-points");
  ecs_component_create(AttributeType, "attribute-type");

  ecs_empty_component_create("input");
  ecs_empty_component_create("total-attribute-points");
}
