#include "include/components.h"
#include "include/ecs.h"
#include "include/math.h"
#include "include/renderer.h"
#include "include/tilemap.h"

void
prefab_player(V2f position) {
  position = tilemap_snap_to_grid(position);
  ecs_entity_creation_begin("position", "position-interpolation", "speed", "color", "input", "bump");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(PositionInterpolation, "position-interpolation", ((PositionInterpolation){ position, position, 1.0f }));
    ecs_entity_creation_setup_component(f32, "speed", 6.0f);
    ecs_entity_creation_setup_component(Color, "color", C_YELLOW);
    ecs_entity_creation_setup_component(bool, "bump", false);
  ecs_entity_creation_end();
}

void
prefab_solid(V2f position) {
  position = tilemap_snap_to_grid(position);
  ecs_entity_creation_begin("position", "color");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(Color, "color", C_GREEN);
  ecs_entity_creation_end();
}
