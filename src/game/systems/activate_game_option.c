#include "engine/ecs.h"
#include "engine/types.h"
#include "game/components.h"
#include "general/global.h"

void
system_activate_game_option(void) {
  bool *active = ecs_get_component_list("active");
  InGameMenuType *menu_type = ecs_get_component_list("in-game-menu-type");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    active[e] = menu_type[e] == global.game.menu_type;
  }
}
