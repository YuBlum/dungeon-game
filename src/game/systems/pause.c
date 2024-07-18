#include "engine/ecs.h"
#include "engine/input.h"
#include "game/components.h"
#include "general/global.h"

void
system_pause(void) {
  bool *pause = ecs_get_component_list("pause");
  for (Entity e = 0; e < ecs_entities_amount(); e++) {
    if (input_key_pressed(KEY_B)) {
      pause[e] = !pause[e];
      if (pause[e]) {
        ecs_system_pause_event(ON_PRE_UPDATE);
        ecs_system_pause_event(ON_UPDATE);
        ecs_system_pause_event(ON_POS_UPDATE);
        ecs_system_pause_event(ON_PRE_DRAW_UI);
        ecs_system_pause_event(ON_DRAW_UI);
        ecs_system_pause_event(ON_POS_DRAW_UI);
        ecs_system_unpause("pause");
        ecs_system_unpause("cursor-navigation");
        ecs_system_unpause("draw-option-ui");
        ecs_system_unpause("select-option");
        ecs_system_unpause("global-cursor-update");
        ecs_system_unpause("activate-game-option");
        ecs_system_unpause("in-game-menu-title");
        ecs_system_unpause("draw-carrying-weight");
        ecs_system_unpause("draw-item");
        ecs_system_unpause("inventory-header");
        ecs_system_unpause("reset-items-amount");
        ecs_system_unpause("update-items-amount");
        ecs_system_unpause("items-offset");
        global.menu.cursor_id = 0;
        global.menu.option_id[0] = 0;
        global.menu.cursor_id_prv = 0;
        global.menu.option_id_prv[0] = 0;
        global.menu.option_amount[0] = 3 + (global.game.class == CLASS_WIZARD);
        global.game.menu_type = IGM_PAUSE;
      } else {
        ecs_system_unpause_event(ON_PRE_UPDATE);
        ecs_system_unpause_event(ON_UPDATE);
        ecs_system_unpause_event(ON_POS_UPDATE);
        ecs_system_unpause_event(ON_PRE_DRAW_UI);
        ecs_system_unpause_event(ON_DRAW_UI);
        ecs_system_unpause_event(ON_POS_DRAW_UI);
        ecs_system_pause("cursor-navigation");
        ecs_system_pause("draw-option-ui");
        ecs_system_pause("select-option");
        ecs_system_pause("global-cursor-update");
      }
    }
    if (!pause[e]) {
      global.game.menu_type = IGM_NONE;
    }
  }
}
