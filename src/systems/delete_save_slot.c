#include "include/components.h"
#include "include/core.h"
#include "include/ecs.h"
#include "include/global.h"
#include "include/input.h"
#include "include/scene_manager.h"
#include "include/scenes.h"
#include <stdio.h>

void
delete_save_slot_system(void) {
  u32 *id = ecs_get_component_list("option-id");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  CharacterName *character_name = ecs_get_component_list("character-name");
  char path[SAVE_PATH_SIZE];
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (global.cursor_id != cursor_id[e] || global.option_id[cursor_id[e]] != id[e] || !input_key_pressed(KEY_A) || character_name[e].size == 0) continue;
    snprintf(path, SAVE_PATH_SIZE, SAVE_PATH_FMT, id[e]);
    remove(path);
    scene_manager_goto_scene(save_slots_menu_scene);
  }
}
