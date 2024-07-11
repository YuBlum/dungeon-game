#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

#include "include/math.h"
#include "include/types.h"

typedef struct {
  i32 agility;
  i32 intelect;
  i32 presence;
  i32 strength;
  i32 vigor;
} Attributes;

typedef struct {
  u32 hit_points_cur;
  u32 hit_points_max;
  u32 armour_points;
} DefensiveStats;

typedef enum {
  CLASS_FIGHTER = 0,
  CLASS_THIEF,
  CLASS_WIZARD
} Class;

typedef struct {
  u32 essence_points_cur;
  u32 essence_points_max;
  u32 food_points_cur;
  u32 food_points_max;
  u32 experience;
  u32 level;
} CharSheet;

#define CHAR_NAME_CAP 10
typedef struct {
  char buff[CHAR_NAME_CAP];
  u32 size;
} CharName;

typedef struct {
  V2f prv;
  V2f nxt;
  f32 timer;
} PositionLerp;

typedef void(*OptionCallback)(void);

void components_create(void);

#endif/*__COMPONENTS_H__*/
