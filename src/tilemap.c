#include "include/tilemap.h"
#include "include/core.h"
#include "include/math.h"
#include "include/renderer.h"
#include "include/types.h"
#include "include/prefabs.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  TileType *data;
  usize width;
  usize height;
} Tilemap;

static Tilemap tilemap;

#if DEVMODE
static const char *tile_type_str[] = {
  "TILE_NONE",
  "TILE_SOLID",
  "TILE_PLAYER",
};
_Static_assert(sizeof (tile_type_str) / sizeof (char *) == TILE_TYPE_AMOUNT, "'tile_type_str' doesn't handle all tile types");
#endif

void
tilemap_setup(usize width, usize height) {
#if DEVMODE
  (void)tile_type_str;
#endif
  usize amount = width * height * sizeof (TileType);
  tilemap.width = width;
  tilemap.height = height;
  tilemap.data = !tilemap.data ? malloc(amount) : realloc(tilemap.data, amount);
  memset(tilemap.data, TILE_NONE, amount);
}

TileType
__tilemap_get(V2f position, const char *file, u32 line) {
  i32 tile_x = position.x + tilemap.width * 0.5f - 0.5f;
  i32 tile_y = position.y + tilemap.height * 0.5f - 0.5f;
#if DEVMODE
  if (!tilemap.data) ERROR("%s:%u: Trying to get tile, but tilemap doesn't exists", file, line);
  if (tile_x < 0 || (usize)tile_x >= tilemap.width || tile_y < 0 || (usize)tile_y >= tilemap.height) ERROR("%s:%u: Out of bounds tile (%d, %d)", file, line, tile_x, tile_y);
#endif
  return tilemap.data[tile_y * tilemap.width + tile_x];
}

void
__tilemap_set(V2f position, TileType type, bool create_entity, const char *file, u32 line) {
  i32 tile_x = ceilf(position.x + tilemap.width * 0.5f - 1);
  i32 tile_y = ceilf(position.y + tilemap.height * 0.5f - 1);
  position.x = tile_x - tilemap.width * 0.5f + 0.5f;
  position.y = tile_y - tilemap.height * 0.5f + 0.5f;
#if DEVMODE
  if (!tilemap.data) ERROR("%s:%u: Trying to set tile, but tilemap doesn't exists", file, line);
  if (tile_x < 0 || (usize)tile_x >= tilemap.width || tile_y < 0 || (usize)tile_y >= tilemap.height) ERROR("%s:%u: Out of bounds tile (%d, %d)", file, line, tile_x, tile_y);
#endif
  tilemap.data[tile_y * tilemap.width + tile_x] = type;
#if DEVMODE
  _Static_assert(TILE_TYPE_AMOUNT == 3, "Not all tile types are handled here");
#endif
  if (!create_entity) return;
  switch (type) {
    case TILE_SOLID:
      prefab_solid(V2FV(position));
      break;
    case TILE_PLAYER:
      prefab_player(V2FV(position));
      break;
    default: break;
  }
}

void
tilemap_draw(void) {
  V2f position;
  position.y = tilemap.height * -0.5f + 0.5f;
  for (usize y = 0; y < tilemap.height; y++) {
    position.x = tilemap.width * -0.5f + 0.5f;
    for (usize x = 0; x < tilemap.width; x++) {
      Color color;
      switch (tilemap.data[y * tilemap.width + x]) {
        case TILE_SOLID:
          color = 0xFF0000CC;
          break;
        case TILE_PLAYER:
          color = 0x0000FFCC;
          break;
        default:
          color = 0xFFFFFFCC;
          break;
      }
      renderer_request_quad(position, V2FS(0.9f), color, 1);
      position.x++;
    }
    position.y++;
  }
}
