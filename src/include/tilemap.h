#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "include/ecs.h"
#include "include/math.h"
#include "include/types.h"

void tilemap_setup(usize width, usize height);
V2f __tilemap_snap_to_grid(V2f position, const char *file, u32 line);
EntityReference __tilemap_get(V2f position, const char *file, u32 line);
void __tilemap_set(V2f position, Entity e, const char *file, u32 line);
void __tilemap_clear(V2f position, const char *file, u32 line);
void tilemap_draw(void);

#define tilemap_snap_to_grid(POSITION) __tilemap_snap_to_grid(POSITION, __FILE__, __LINE__)
#define tilemap_get(POSITION) __tilemap_get(POSITION, __FILE__, __LINE__)
#define tilemap_set(POSITION, ENTITY) __tilemap_set(POSITION, ENTITY, __FILE__, __LINE__)
#define tilemap_clear(POSITION) __tilemap_clear(POSITION, __FILE__, __LINE__)

#endif/*__TILEMAP_H__*/
