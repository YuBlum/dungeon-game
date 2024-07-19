#include "game/components.h"
#include "engine/ecs.h"
#include "engine/input.h"
#include "general/global.h"

void
system_type_character_name_input(usize entities_amount) {
  CharacterName *character_name = ecs_get_component_list("character-name");
  u32 *id = ecs_get_component_list("option-id");
  u32 *cursor_id = ecs_get_component_list("cursor-id");
  for (Entity e = 0; e < entities_amount; e++) {
    if (global.menu.cursor_id != cursor_id[e] || global.menu.option_id[cursor_id[e]] != id[e]) continue;
    char letter = input_letter_pressed();
    if (letter != -1 && character_name[e].size < CHARACTER_NAME_CAP) {
      if (character_name[e].size == 0 && letter >= 'a' && letter <= 'z') {
        letter -= 32;
      } else if (character_name[e].size > 0 && letter >= 'A' && letter <= 'Z') {
        letter += 32;
      }
      character_name[e].buff[character_name[e].size] = letter;
      character_name[e].size++;
    } else if (input_key_repeated(KEY_BACKSPACE) && character_name[e].size > 0) {
      character_name[e].size--;
    }
    global.character_creation.has_name = character_name[e].size > 0;
  }
}
