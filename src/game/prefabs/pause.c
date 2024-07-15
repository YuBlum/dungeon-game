#include "engine/ecs.h"

void
prefab_pause(void) {
  ecs_entity_creation_begin("pause");
  ecs_entity_creation_end();
}
