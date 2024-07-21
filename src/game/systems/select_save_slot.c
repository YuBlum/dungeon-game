#include "game/components.h"
#include "general/global.h"
#include "engine/ecs.h"
#include "engine/input.h"
#include "engine/scene_manager.h"
#include "engine/serialization.h"

void
system_select_save_slot(usize entities_amount) {
  u32 *id = ecs_get_component_list("option-id");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  CharacterName *character_name = ecs_get_component_list("character-name");
  for (Entity e = 0; e < entities_amount; e++) {
    if (global.menu.cursor_id != cursor_id[e] || global.menu.option_id[cursor_id[e]] != id[e] || !input_key_pressed(KEY_A)) continue;
    global.all.save_slot = id[e];
    if (character_name[e].size) {
      serialization_start();
      scene_manager_goto("overworld");
    } else {
      scene_manager_goto("character-creation");
    }
  }
}
