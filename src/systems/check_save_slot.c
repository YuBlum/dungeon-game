#include "include/components.h"
#include "include/ecs.h"
#include <stdio.h>

#define SAVE_PATH "res/saves/slot.save"

void
check_save_slot_system(void) {
  CharName *char_name = ecs_get_component_list("char-name");
  Class *class = ecs_get_component_list("class");
  i32 *option_id = ecs_get_component_list("option-id");
  char path[sizeof (SAVE_PATH) + 1];
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    sprintf(path, "res/saves/slot%d.save", option_id[e]);
    FILE *f = fopen(path, "rb");
    if (!f) continue;
    fread(&char_name[e].size, sizeof (u32), 1, f);
    fread(char_name[e].buff, sizeof (char), char_name[e].size, f);
    fread(&class[e], sizeof (Class), 1, f);
    fclose(f);
  }
}
