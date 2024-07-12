#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "include/components.h"
#include "include/types.h"

#define GLOBAL_OPTION_ID_CAP 5
typedef struct {
  f32 dt;
  bool split_screen;
  i32 save_slot;
  u32 cursor_id;
  u32 cursor_id_prv;
  u32 option_id[GLOBAL_OPTION_ID_CAP];
  u32 attribute_points;
  Class class;
  Class class_prv;
} Global;

extern Global global;

#endif/*__GLOBAL_H__*/
