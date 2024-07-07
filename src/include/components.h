#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

#include "include/math.h"
#include "include/types.h"

typedef u8 Tag;

typedef struct {
  i32 agility;
  i32 intelect;
  i32 strength;
  i32 vigor;
} Attributes;

typedef struct {
  u32 hp;
  u32 ep;
  u32 fp;
} Stats;

typedef struct {
  V2f prv;
  V2f nxt;
  f32 timer;
} PositionInterpolation;

void components_create(void);

#endif/*__COMPONENTS_H__*/
