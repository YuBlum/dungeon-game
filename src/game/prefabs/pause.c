#include "engine/types.h"
#include "engine/ecs.h"
#include "engine/serialization.h"
#include "engine/scene_manager.h"
#include "game/components.h"
#include "game/prefabs.h"
#include "general/global.h"

static void
inventory_option(void) {
  global.game.menu_type = IGM_INVENTORY;
  global.menu.cursor_id = global.game.items_cursor_id;
  global.menu.option_id[global.game.items_cursor_id] = 0;
  global.menu.cursor_id_prv = global.game.items_cursor_id;
  global.menu.option_id_prv[global.game.items_cursor_id] = 0;
  global.game.items_offset = 0;
  global.game.items_cursor_min = 0;
  global.game.items_cursor_max = 3;
  ecs_system_unpause("draw-carrying-weight");
  ecs_system_unpause("draw-item");
  ecs_system_unpause("items-offset");
  ecs_system_unpause("select-item");
  ecs_system_unpause("update-item-id");
  ecs_system_unpause("item-melee-description");
  ecs_system_unpause("item-ranged-description");
  ecs_system_unpause("item-staff-description");
  ecs_system_unpause("item-defensive-description");
  ecs_system_unpause("item-potion-description");
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
  scene_manager_goto("main-menu");
}

void
prefab_pause(void) {
  ecs_entity_creation_begin("pause");
    ecs_entity_creation_setup_component(bool, "pause", false);
  ecs_entity_creation_end();

  ecs_system_pause("cursor-navigation");
  ecs_system_pause("draw-option-ui");
  ecs_system_pause("select-option");
  ecs_system_pause("draw-carrying-weight");
  ecs_system_pause("draw-item");
  ecs_system_pause("items-offset");
  ecs_system_pause("select-item");
  ecs_system_pause("update-item-id");
  ecs_system_pause("item-melee-description");
  ecs_system_pause("item-ranged-description");
  ecs_system_pause("item-staff-description");
  ecs_system_pause("item-defensive-description");
  ecs_system_pause("item-potion-description");

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

  prefab_menu_cursor(0, false, true);
  prefab_menu_cursor(1, false, false);
  global.game.items_cursor_id = 1;
}
