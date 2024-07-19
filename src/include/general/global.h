#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "game/components.h"
#include "engine/types.h"

#define GLOBAL_MENU_CURSOR_CAP 5
typedef struct {
  u32 cursor_id;
  u32 cursor_id_prv;
  u32 option_amount[GLOBAL_MENU_CURSOR_CAP];
  u32 option_id[GLOBAL_MENU_CURSOR_CAP];
  u32 option_id_prv[GLOBAL_MENU_CURSOR_CAP];
} GlobalMenu;

typedef struct {
  u32 total_attribute_points;
  Class class;
  Class class_prv;
  bool has_name;
} GlobalCharacterCreation;

typedef struct {
  f32 dt;
  bool split_screen;
  i32 save_slot;
} GlobalAll;


#define ITEM_DESCRIPTION_LINE_CAP 4
#define ITEM_DESCRIPTION_LINE_STR_CAP 21
typedef struct {
  char  line_buff[ITEM_DESCRIPTION_LINE_CAP][ITEM_DESCRIPTION_LINE_STR_CAP];
  u32   line_size[ITEM_DESCRIPTION_LINE_CAP];
  Color line_color[ITEM_DESCRIPTION_LINE_CAP];
} ItemDescription;

typedef struct {
  InGameMenuType menu_type;
  Class class;
  f32 inventory_y;
  u32 items_amount;
  f32 items_offset;
  ItemDescription item_description;
} GlobalGame;

typedef struct {
  GlobalAll all;
  GlobalMenu menu;
  GlobalGame game;
  GlobalCharacterCreation character_creation;
} Global;

extern Global global;

#endif/*__GLOBAL_H__*/
