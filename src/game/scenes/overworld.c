#include "general/core.h"
#include "general/global.h"
#include "engine/tilemap.h"
#include "game/prefabs.h"

void
overworld_scene(void) {
  global.all.split_screen = true;
  tilemap_setup(GAME_W, GAME_H);
  prefab_player(V2FS(0));
}
