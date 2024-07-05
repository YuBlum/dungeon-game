#include "include/components.h"
#include "include/ecs.h"
#include "include/math.h"
#include "include/renderer.h"

void
prefab_player(V2f position) {
  ecs_entity_creation_begin("position", "move-position", "color", "input");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(MovePosition, "move-position", ((MovePosition){ position, position, 1.0f, 6.0f }));
    ecs_entity_creation_setup_component(Color, "color", C_YELLOW);
    ecs_entity_creation_setup_component(bool, "input", true);
  ecs_entity_creation_end();
}
