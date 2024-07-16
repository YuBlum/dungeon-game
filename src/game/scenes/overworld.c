#include "game/scenes.h"
#include "general/core.h"
#include "general/global.h"
#include "engine/tilemap.h"
#include "game/prefabs.h"

void
scene_overworld(void) {
  global.all.split_screen = true;
  tilemap_setup(GAME_W, GAME_H);
  prefab_terminal();
  prefab_player(V2FS(1));
  prefab_pause();
}
