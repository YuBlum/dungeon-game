#include "engine/ecs.h"
#include "engine/input.h"
#include "game/components.h"
#include "general/global.h"

void
system_pause(usize entities_amount) {
  bool *pause = ecs_get_component_list("pause");
  for (Entity e = 0; e < entities_amount; e++) {
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
        ecs_system_unpause("activate-game-option");
        ecs_system_unpause("grow-items-amount");
        ecs_system_unpause("shrink-items-amount");
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
        ecs_system_pause("draw-carrying-weight");
        ecs_system_pause("draw-item");
        ecs_system_pause("grow-items-amount");
        ecs_system_pause("shrink-items-amount");
        ecs_system_pause("items-offset");
        ecs_system_pause("select-item");
        ecs_system_pause("update-item-id");
      }
    }
    if (!pause[e]) {
      global.game.menu_type = IGM_NONE;
    }
  }
}
