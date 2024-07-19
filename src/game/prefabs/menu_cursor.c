#include "game/components.h"
#include "engine/ecs.h"

void
prefab_menu_cursor(u32 id, bool horizontal, bool wrap) {
  ecs_entity_creation_begin("cursor", "cursor-id");
    ecs_entity_creation_setup_component(Cursor, "cursor", ((Cursor) { horizontal, wrap }));
    ecs_entity_creation_setup_component(u32, "cursor-id", id);
  ecs_entity_creation_end();
}
