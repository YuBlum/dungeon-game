#include "game/components.h"
#include "engine/ecs.h"
#include "engine/math.h"

void
prefab_menu_hint(V2f position) {
  ecs_entity_creation_begin("position", "menu-hint", "tag", "color");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(Tag, "tag", "");
  ecs_entity_creation_end();
}
