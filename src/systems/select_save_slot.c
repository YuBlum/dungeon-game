#include "include/components.h"
#include "include/ecs.h"
#include "include/global.h"
#include "include/input.h"
#include "include/scene_manager.h"
#include "include/scenes.h"
#include "include/serialization.h"

void
select_save_slot_system(void) {
  u32 *id = ecs_get_component_list("option-id");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  CharacterName *character_name = ecs_get_component_list("character-name");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (global.menu.cursor_id != cursor_id[e] || global.menu.option_id[cursor_id[e]] != id[e] || !input_key_pressed(KEY_A)) continue;
    global.all.save_slot = id[e];
    if (character_name[e].size) {
      serialization_start();
      scene_manager_goto_scene(overworld_scene);
    } else {
      scene_manager_goto_scene(character_creation_scene);
    }
  }
}
