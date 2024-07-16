#include "engine/types.h"
#include "engine/ecs.h"
#include "engine/serialization.h"
#include "engine/scene_manager.h"
#include "game/components.h"
#include "general/core.h"
#include "game/scenes.h"
#include "game/prefabs.h"
#include "general/global.h"

static void
inventory_option(void) {
  global.game.menu_type = IGM_INVENTORY;
}

static void
abilities_option(void) {
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
prefab_pause(void) {
  ecs_entity_creation_begin("pause");
    ecs_entity_creation_setup_component(bool, "pause", false);
  ecs_entity_creation_end();

  ecs_system_pause("cursor-navigation");
  ecs_system_pause("draw-option-ui");
  ecs_system_pause("select-option");
  ecs_system_pause("global-cursor-update");

  global.game.menu_type = IGM_NONE;
  V2f position = { 0, 2.5f };
  u32 option_id = 0;
  prefab_in_game_menu_option(position, "Inventory (E)", (Callback)inventory_option, 0, option_id++, 0, false, IGM_PAUSE);
  position.y -= 2;
  prefab_in_game_menu_option(position, "Abilities (A)", (Callback)abilities_option, 0, option_id++, 0, false, IGM_PAUSE);
  if (global.game.class == CLASS_WIZARD) {
    position.y -= 2;
    prefab_in_game_menu_option(position, "Spells (S)", (Callback)spells_option, 0, option_id++, 0, false, IGM_PAUSE);
  }
  position.y -= 2;
  prefab_in_game_menu_option(position, "Go to Menu", (Callback)go_to_menu_option, 0, option_id++, 0, false, IGM_PAUSE);

  prefab_menu_cursor(0, false);
}
