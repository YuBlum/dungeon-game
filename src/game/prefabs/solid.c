#include "engine/ecs.h"
#include "engine/renderer.h"
#include "engine/tilemap.h"

void
prefab_solid(V2f position) {
  position = tilemap_snap_to_grid(position);
  ecs_entity_creation_begin("position", "color", "tile");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(Color, "color", 0x00aa55ff);
  ecs_entity_creation_end();
}
