#include "engine/ecs.h"

void
new_character_setup_system(void) {
  EntityReference **reference_ptr = ecs_get_component_list("reference-ptr");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    ecs_entity_get_reference(reference_ptr[e], e);
  }
}
