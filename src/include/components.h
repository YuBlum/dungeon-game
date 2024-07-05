#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

#include "include/math.h"

typedef struct {
  V2f prv;
  V2f nxt;
  f32 timer;
  f32 speed;
} MovePosition;

void components_create(void);

#endif/*__COMPONENTS_H__*/
