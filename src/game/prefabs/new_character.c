#include "engine/ecs.h"

void
prefab_new_character(EntityReference *reference) {
  ecs_entity_creation_begin("character-name", "class", "attributes", "reference-ptr");
    ecs_entity_creation_setup_component(EntityReference *, "reference-ptr", reference);
  ecs_entity_creation_end();
}
