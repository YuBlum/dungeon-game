#include "include/ecs.h"
#include "include/global.h"
#include "include/types.h"

void
global_cursor_update_system(void) {
  u32 *id = ecs_get_component_list("cursor-id");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (global.cursor_id == id[e]) global.cursor_id_prv = id[e];
  }
}
