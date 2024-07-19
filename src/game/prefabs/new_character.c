#include "engine/ecs.h"

void
prefab_new_character(EntityReference *reference) {
  ecs_entity_creation_begin("character-name", "class", "attributes");
    ecs_entity_creation_get_reference(reference);
  ecs_entity_creation_end();
}
