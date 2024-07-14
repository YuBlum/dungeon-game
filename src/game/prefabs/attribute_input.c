#include "game/components.h"
#include "engine/ecs.h"
#include "engine/math.h"

void
prefab_attribute_input(V2f position, AttributeType attribute_type, u32 id, u32 cursor_id, Callback get_attribute) {
  ecs_entity_creation_begin("position", "attribute-type", "option-id", "cursor-id", "attribute-points", "callback");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(AttributeType, "attribute-type", attribute_type);
    ecs_entity_creation_setup_component(u32, "option-id", id);
    ecs_entity_creation_setup_component(u32, "cursor-id", cursor_id);
    ecs_entity_creation_setup_component(i32, "attribute-points", -2);
    ecs_entity_creation_setup_component(Callback, "callback", get_attribute);
  ecs_entity_creation_end();
}
