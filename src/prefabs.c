#include "include/ecs.h"
#include "include/math.h"
#include "include/renderer.h"

void
prefab_rect(V2f position, V2f size, Color color) {
  ecs_entity_creation_begin("position", "size", "color");
    ecs_entity_creation_setup_component(V2f,   "position", position);
    ecs_entity_creation_setup_component(V2f,   "size",     size    );
    ecs_entity_creation_setup_component(Color, "color",    color   );
  ecs_entity_creation_end();
}
