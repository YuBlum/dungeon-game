#include "game/components.h"
#include "engine/ecs.h"
#include "general/global.h"

void
system_submit_character_input(usize entities_amount) {
  CharacterName *character_name = ecs_get_component_list("character-name");
  u32 *id = ecs_get_component_list("option-id");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  Callback *callback = ecs_get_component_list("callback");
  for (Entity e = 0; e < entities_amount; e++) {
    if (global.menu.cursor_id != cursor_id[e] || global.menu.option_id_prv[cursor_id[e]] != id[e] || global.menu.option_id[cursor_id[e]] == id[e]) continue;
    callback[e](&character_name[e]);
  }
}
