#include "engine/ecs.h"
#include "game/components.h"

void
prefab_terminal(void) {
  ecs_entity_creation_begin("terminal");
    ecs_entity_creation_setup_component(Terminal, "terminal", ((Terminal){ 0 }));
  ecs_entity_creation_end();
}
