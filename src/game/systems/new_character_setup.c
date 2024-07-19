#include "engine/ecs.h"

void
system_new_character_setup(usize entities_amount) {
  EntityReference **reference_ptr = ecs_get_component_list("reference-ptr");
  for (Entity e = 0; e < entities_amount; e++) {
    ecs_entity_get_reference(reference_ptr[e], e);
  }
}
