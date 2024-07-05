#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "include/math.h"
#include "include/types.h"

typedef enum {
  TILE_NONE = 0,
  TILE_SOLID,
  TILE_PLAYER,

  TILE_TYPE_AMOUNT
} TileType;

void tilemap_setup(usize width, usize height);
TileType __tilemap_get(V2f position, const char *file, u32 line);
void __tilemap_set(V2f position, TileType type, bool create_entity, const char *file, u32 line);
void tilemap_draw(void);

#define tilemap_get(POSITION) __tilemap_get(POSITION, __FILE__, __LINE__)
#define tilemap_set(POSITION, TYPE, CREATE_ENTITY) __tilemap_set(POSITION, TYPE, CREATE_ENTITY, __FILE__, __LINE__)

#endif/*__TILEMAP_H__*/
