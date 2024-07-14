#include "general/core.h"
#include "general/global.h"
#include "engine/scene_manager.h"
#include "game/prefabs.h"
#include "game/scenes.h"
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
  scene_manager_goto_scene(main_menu_scene);
}

static void
delete_save_option(void) {
  scene_manager_goto_scene(delete_save_menu_scene);
}

void
save_slots_menu_scene(void) {
  global.all.split_screen = false;
  global.menu.option_id[0] = 0;
  global.menu.cursor_id = 0;
  global.menu.cursor_id_prv = 0;
  V2f position = { 0.0f, 3.0f };
  u32 cursor_id = 0;
  prefab_save_slot(position, cursor_id++, 0);
  position.y -= 2;
  prefab_save_slot(position, cursor_id++, 0);
  position.y -= 2;
  prefab_save_slot(position, cursor_id++, 0);
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
    prefab_menu_option(position, "Delete Save", (Callback)delete_save_option, 0, cursor_id++, 0);
    position.y -= 2;
  }
  prefab_menu_option(position, "Go Back", (Callback)go_back_option, 0, cursor_id++, 0);
  prefab_menu_cursor(cursor_id, 0, false);
}
