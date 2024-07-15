#include "engine/ecs.h"
#include "engine/types.h"

void
prefab_pause(void) {
  ecs_system_pause("cursor-navigation");
  ecs_system_pause("draw-option-ui");
  ecs_system_pause("select-option");
  ecs_system_pause("global-cursor-update");
  ecs_entity_creation_begin("pause");
    ecs_entity_creation_setup_component(bool, "pause", false);
  ecs_entity_creation_end();
}
