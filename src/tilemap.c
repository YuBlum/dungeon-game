#include "include/tilemap.h"
#include "include/core.h"
#include "include/ecs.h"
#include "include/math.h"
#include "include/renderer.h"
#include "include/types.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  EntityReference *map;
  usize width;
  usize height;
} Tilemap;

static Tilemap tilemap;

void
tilemap_setup(usize width, usize height) {
  usize amount = width * height * sizeof (EntityReference);
  tilemap.width = width;
  tilemap.height = height;
  tilemap.map = !tilemap.map ? malloc(amount) : realloc(tilemap.map, amount);
  memset(tilemap.map, 0, amount);
}

V2f
__tilemap_snap_to_grid(V2f position, const char *file, u32 line) {
#if DEVMODE
  if (!tilemap.map) ERROR("%s:%u: Trying to snap position to grid, but tilemap doesn't exists", file, line);
#endif
  return V2F(
    ceilf(position.x + tilemap.width * 0.5f - 1) - tilemap.width * 0.5f + 0.5f,
    ceilf(position.y + tilemap.height * 0.5f - 1) - tilemap.height * 0.5f + 0.5f
  );
}

bool
__tilemap_is_in_bounds(V2f position, const char *file, u32 line) {
  i32 tile_x = position.x + tilemap.width * 0.5f - 0.5f;
  i32 tile_y = position.y + tilemap.height * 0.5f - 0.5f;
#if DEVMODE
  if (!tilemap.map) ERROR("%s:%u: Trying to check if out of bounds, but tilemap doesn't exists", file, line);
#endif
  return tile_x >= 0 && (usize)tile_x < tilemap.width && tile_y >= 0 && (usize)tile_y < tilemap.height;
}

EntityReference
__tilemap_get(V2f position, const char *file, u32 line) {
  i32 tile_x = position.x + tilemap.width * 0.5f - 0.5f;
  i32 tile_y = position.y + tilemap.height * 0.5f - 0.5f;
#if DEVMODE
  if (!tilemap.map) ERROR("%s:%u: Trying to get tile, but tilemap doesn't exists", file, line);
  if (tile_x < 0 || (usize)tile_x >= tilemap.width || tile_y < 0 || (usize)tile_y >= tilemap.height) ERROR("%s:%u: Out of bounds tile (%d, %d)", file, line, tile_x, tile_y);
#endif
  return tilemap.map[tile_y * tilemap.width + tile_x];
}

void
__tilemap_set(V2f position, Entity e, const char *file, u32 line) {
  i32 tile_x = position.x + tilemap.width * 0.5f - 0.5f;
  i32 tile_y = position.y + tilemap.height * 0.5f - 0.5f;
#if DEVMODE
  if (!tilemap.map) ERROR("%s:%u: Trying to set tile, but tilemap doesn't exists", file, line);
  if (tile_x < 0 || (usize)tile_x >= tilemap.width || tile_y < 0 || (usize)tile_y >= tilemap.height) ERROR("%s:%u: Out of bounds tile (%d, %d)", file, line, tile_x, tile_y);
#endif
  EntityReference *tile = &tilemap.map[tile_y * tilemap.width + tile_x];
  __ecs_entity_get_reference(tile, e, file, line);
}

void
__tilemap_clear(V2f position, const char *file, u32 line) {
  i32 tile_x = position.x + tilemap.width * 0.5f - 0.5f;
  i32 tile_y = position.y + tilemap.height * 0.5f - 0.5f;
#if DEVMODE
  if (!tilemap.map) ERROR("%s:%u: Trying to set tile, but tilemap doesn't exists", file, line);
  if (tile_x < 0 || (usize)tile_x >= tilemap.width || tile_y < 0 || (usize)tile_y >= tilemap.height) ERROR("%s:%u: Out of bounds tile (%d, %d)", file, line, tile_x, tile_y);
#endif
  EntityReference *tile = &tilemap.map[tile_y * tilemap.width + tile_x];
  if (*tile) __ecs_entity_clean_reference(tile, file, line);
}

void
tilemap_draw(void) {
  return;
#if DEVMODE
  V2f position;
  position.y = tilemap.height * -0.5f + 0.5f;
  for (usize y = 0; y < tilemap.height; y++) {
    position.x = tilemap.width * -0.5f + 0.5f;
    for (usize x = 0; x < tilemap.width; x++) {
      Color color;
      switch (tilemap.map[y * tilemap.width + x]) {
        case 0:
          color = 0xFFFFFFCC;
          break;
        default:
          color = 0xFF0000CC;
          break;
      }
      (void)color;
      //renderer_rect(position, V2FS(0.9f), color, 1);
      position.x++;
    }
    position.y++;
  }
#endif
}
