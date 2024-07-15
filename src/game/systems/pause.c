#include "engine/ecs.h"
#include "engine/input.h"
#include "engine/scene_manager.h"
#include "engine/serialization.h"
#include "general/core.h"
#include "general/global.h"
#include "game/scenes.h"
#include "game/prefabs.h"

static void
abilities_option(void) {
  WARN("Not Implemented");
}

static void
inventory_option(void) {
  WARN("Not Implemented");
}

static void
spells_option(void) {
  WARN("Not Implemented");
}

static void
go_to_menu_option(void) {
  serialization_end();
  scene_manager_goto(scene_main_menu);
}

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
        global.menu.cursor_id = 0;
        global.menu.option_id[0] = 0;
        global.menu.cursor_id_prv = 0;
        global.menu.option_id_prv[0] = 0;
        Class class;
        deserialize(CHARACTER_SHEET_CLASS, &class);

        V2f position = { 0, 2.5f };
        u32 option_id = 0;
        prefab_menu_option(position, "Inventory [C]", (Callback)inventory_option, 0, option_id++, 0);
        position.y -= 2;
        prefab_menu_option(position, "Abilities [A]", (Callback)abilities_option, 0, option_id++, 0);
        if (class == CLASS_WIZARD) {
          position.y -= 2;
          prefab_menu_option(position, "Spells [S]", (Callback)spells_option, 0, option_id++, 0);
        }
        position.y -= 2;
        prefab_menu_option(position, "Go to Menu", (Callback)go_to_menu_option, 0, option_id++, 0);
        prefab_menu_cursor(option_id, 0, false);
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
  }
}
