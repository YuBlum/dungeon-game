#include "include/components.h"
#include "include/ecs.h"
#include "include/math.h"
#include "include/renderer.h"
#include "include/tilemap.h"

void
prefab_player(V2f position) {
  ecs_entity_creation_begin("position", "move-position", "color", "input", "tile-type");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(MovePosition, "move-position", ((MovePosition){ position, position, 1.0f, 6.0f }));
    ecs_entity_creation_setup_component(Color, "color", C_YELLOW);
    ecs_entity_creation_setup_component(TileType, "tile-type", TILE_PLAYER);
  ecs_entity_creation_end();
}

void
prefab_solid(V2f position) {
  ecs_entity_creation_begin("position", "color");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(Color, "color", C_GREEN);
  ecs_entity_creation_end();
}
