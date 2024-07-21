#include "general/core.h"
#include "general/global.h"
#include "engine/scene_manager.h"
#include "game/prefabs.h"
#include <stdio.h>
#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#else
#include <unistd.h>
#endif

static void
go_back_option(void) {
  scene_manager_goto("main-menu");
}

static void
delete_save_option(void) {
  scene_manager_goto("delete-save-menu");
}

void
scene_save_slots_menu_on_start(void) {
  global.all.split_screen = false;
  global.menu.option_id[0] = 0;
  global.menu.cursor_id = 0;
  global.menu.cursor_id_prv = 0;
  V2f position = { 0.0f, 3.0f };
  global.menu.option_amount[0] = 0;
  prefab_save_slot(position, global.menu.option_amount[0]++, 0);
  position.y -= 2;
  prefab_save_slot(position, global.menu.option_amount[0]++, 0);
  position.y -= 2;
  prefab_save_slot(position, global.menu.option_amount[0]++, 0);
  position.y -= 3;
  char save[3][SAVE_PATH_SIZE];
  bool save_file_exists = false;
  for (u32 i = 0; i < 3; i++) {
    snprintf(save[i], SAVE_PATH_SIZE, SAVE_PATH_FMT, i);
    if (access(save[i], F_OK) == 0) {
      save_file_exists = true;
      break;
    }
  }
  if (save_file_exists) {
    prefab_menu_option(position, "Delete Save", (Callback)delete_save_option, 0, global.menu.option_amount[0]++, 0, true);
    position.y -= 2;
  }
  prefab_menu_option(position, "Go Back", (Callback)go_back_option, 0, global.menu.option_amount[0]++, 0, true);
  prefab_menu_cursor(0, false, true);
}

void
scene_save_slots_menu_on_pre_systems(void) {
  global.menu.cursor_id_prv = global.menu.cursor_id;
}
