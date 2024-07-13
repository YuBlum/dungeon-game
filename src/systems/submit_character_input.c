#include "include/components.h"
#include "include/ecs.h"
#include "include/global.h"

void
submit_character_input_system(void) {
  CharacterName *character_name = ecs_get_component_list("character-name");
  u32 *id = ecs_get_component_list("option-id");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  Callback *callback = ecs_get_component_list("callback");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (global.cursor_id != cursor_id[e] || global.option_id_prv[cursor_id[e]] != id[e] || global.option_id[cursor_id[e]] == id[e]) continue;
    callback[e](&character_name[e]);
  }
}
