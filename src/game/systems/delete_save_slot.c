#include "general/core.h"
#include "general/global.h"
#include "engine/ecs.h"
#include "engine/input.h"
#include "engine/scene_manager.h"
#include "game/components.h"
#include "game/scenes.h"
#include <stdio.h>

void
system_delete_save_slot(void) {
  u32 *id = ecs_get_component_list("option-id");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  CharacterName *character_name = ecs_get_component_list("character-name");
  char path[SAVE_PATH_SIZE];
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (global.menu.cursor_id != cursor_id[e] || global.menu.option_id[cursor_id[e]] != id[e] || !input_key_pressed(KEY_A) || character_name[e].size == 0) continue;
    snprintf(path, SAVE_PATH_SIZE, SAVE_PATH_FMT, id[e]);
    remove(path);
    scene_manager_goto(scene_save_slots_menu);
  }
}
