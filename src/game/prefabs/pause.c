#include "engine/types.h"
#include "engine/ecs.h"
#include "engine/serialization.h"
#include "engine/scene_manager.h"
#include "game/components.h"
#include "game/scenes.h"
#include "game/prefabs.h"
#include "general/global.h"

static void
inventory_option(void) {
  global.game.menu_type = IGM_INVENTORY;
  global.menu.cursor_id = 0;
  global.menu.option_id[0] = 0;
  global.menu.cursor_id = 0;
  global.menu.option_id[0] = 0;
  global.menu.cursor_id_prv = 0;
  global.menu.option_id_prv[0] = 0;
  global.menu.option_amount[0] = global.game.items_amount;
}

static void
abilities_option(void) {
  global.game.menu_type = IGM_ABILITIES;
}

static void
spells_option(void) {
  global.game.menu_type = IGM_SPELLS;
}

static void
go_to_menu_option(void) {
  serialization_end();
  scene_manager_goto(scene_main_menu);
}

/*
static void
inventory_equip_option(void) {
  WARN("Not Implemented");
}

static void
inventory_active_option(void) {
  WARN("Not Implemented");
}

static void
inventory_passive_option(void) {
  WARN("Not Implemented");
}
*/

void
prefab_pause(void) {
  ecs_entity_creation_begin("pause");
    ecs_entity_creation_setup_component(bool, "pause", false);
  ecs_entity_creation_end();

  ecs_system_pause("cursor-navigation");
  ecs_system_pause("draw-option-ui");
  ecs_system_pause("select-option");
  ecs_system_pause("global-cursor-update");

  V2f start_position = { 0, 2.5f };

  global.game.menu_type = IGM_NONE;
  V2f position = start_position;
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

  /*
  position = V2F(-5.5f, UI_TOP - 6.5f);
  option_id = 0;
  prefab_in_game_menu_option(position, "Equip", (Callback)inventory_equip_option, 0, option_id++, 1, false, IGM_INVENTORY);
  position.x += 5.5f;
  prefab_in_game_menu_option(position, "Active", (Callback)inventory_active_option, 0, option_id++, 1, false, IGM_INVENTORY);
  position.x += 5.5f;
  prefab_in_game_menu_option(position, "Passive", (Callback)inventory_passive_option, 0, option_id++, 1, false, IGM_INVENTORY);
  */

  prefab_menu_cursor(0, false);
  //prefab_menu_cursor(1, true);
}
