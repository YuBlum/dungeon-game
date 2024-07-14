#include "include/components.h"
#include "include/ecs.h"
#include "include/serialization.h"

void
check_save_slot_system(void) {
  CharacterName *character_name = ecs_get_component_list("character-name");
  Class *class = ecs_get_component_list("class");
  u32 *id = ecs_get_component_list("option-id");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (deserialize_from_slot_file(CHARACTER_SHEET_NAME_SIZE, id[e], &character_name[e].size)) {
      deserialize_from_slot_file(CHARACTER_SHEET_NAME_BUFF, id[e], character_name[e].buff);
      deserialize_from_slot_file(CHARACTER_SHEET_CLASS, id[e], &class[e]);
    }
  }
}
