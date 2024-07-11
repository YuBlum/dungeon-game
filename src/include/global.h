#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "include/types.h"

typedef struct {
  f32 dt;
  bool split_screen;
  i32 option_id;
} Global;

extern Global global;

#endif/*__GLOBAL_H__*/
