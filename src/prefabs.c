#include "include/components.h"
#include "include/ecs.h"
#include "include/math.h"
#include "include/renderer.h"
#include "include/tilemap.h"
#include "include/prefabs.h"

void
prefab_player(V2f position) {
  position = tilemap_snap_to_grid(position);
  ecs_entity_creation_begin("position", "direction", "position-lerp", "speed", "color", "input", "bump", "attributes", "defensive-stats", "char-sheet");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(V2f, "direction", V2FS(0));
    ecs_entity_creation_setup_component(PositionLerp, "position-lerp", ((PositionLerp){ position, position, 1.0f }));
    ecs_entity_creation_setup_component(f32, "speed", 6.0f);
    ecs_entity_creation_setup_component(Color, "color", 0xffaa00ff);
    ecs_entity_creation_setup_component(bool, "bump", false);
    ecs_entity_creation_setup_component(Attributes, "attributes", ((Attributes){ -1, +0, +1, -2, -1 }));
    ecs_entity_creation_setup_component(DefensiveStats, "defensive-stats", ((DefensiveStats){ 17, 20, 9 }));
    ecs_entity_creation_setup_component(CharSheet, "char-sheet", ((CharSheet){ "Name", 4, 6, 99, 99, 98, 2, CLASS_THIEF }));
  ecs_entity_creation_end();
}

void
prefab_solid(V2f position) {
  position = tilemap_snap_to_grid(position);
  ecs_entity_creation_begin("position", "color");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(Color, "color", 0x00aa55ff);
  ecs_entity_creation_end();
}

void
prefab_menu_option(V2f position, const char *name, OptionCallback callback, i32 option_id) {
  ecs_entity_creation_begin("position", "option-callback", "name", "option-id");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(OptionCallback, "option-callback", callback);
    ecs_entity_creation_setup_component(const char *, "name", name);
    ecs_entity_creation_setup_component(i32, "option-id", option_id);
  ecs_entity_creation_end();
}

void
prefab_menu_cursor(i32 options_amount) {
  ecs_entity_creation_begin("cursor");
    ecs_entity_creation_setup_component(i32, "cursor", options_amount);
  ecs_entity_creation_end();
}
