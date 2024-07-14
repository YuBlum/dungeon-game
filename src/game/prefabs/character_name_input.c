#include "game/components.h"
#include "engine/ecs.h"
#include "engine/math.h"

void
prefab_character_name_input(V2f position, u32 id, u32 cursor_id, Callback get_character_name) {
  ecs_entity_creation_begin("position", "option-id", "cursor-id", "character-name", "callback");
    ecs_entity_creation_setup_component(V2f, "position", position);
    ecs_entity_creation_setup_component(u32, "option-id", id);
    ecs_entity_creation_setup_component(u32, "cursor-id", cursor_id);
    ecs_entity_creation_setup_component(Callback, "callback", get_character_name);
    ecs_entity_creation_setup_component(CharacterName, "character-name", ((CharacterName){ 0 }));
  ecs_entity_creation_end();
}
