#include "include/core.h"
#include "include/global.h"
#include "include/prefabs.h"
#include "include/tilemap.h"

void
overworld_scene(void) {
  global.all.split_screen = true;
  tilemap_setup(GAME_W, GAME_H);
  prefab_solid(V2F(2, 2));
  prefab_solid(V2F(1, 1));
  prefab_solid(V2F(2, 1));
  prefab_solid(V2F(1, 2));
  prefab_player(V2FS(0));
}
