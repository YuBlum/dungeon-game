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
  f32 time;
  bool split_screen;
  i32 save_slot;
} GlobalAll;

typedef struct {
  ItemType type;
  u32 id;
  bool has_item;
} SelectedItem;

typedef enum {
  EQUIP_NONE = 0,
  EQUIP_WEAPON,
  EQUIP_ARMOUR,
  EQUIP_SHIELD
} ItemEquipType;

typedef struct {
  InGameMenuType menu_type;
  InGameMenuType menu_type_prv;
  Class class;
  f32 inventory_y;
  u32 items_amount[ITEM_TYPE_AMOUNT];
  f32 items_offset;
  u32 items_cursor_min;
  u32 items_cursor_max;
  u32 items_cursor_id;
  bool removed_item;
  bool rearranged_item;
  bool fixed_items_order;
  u32 changed_item_id;
  ItemType item_type_page;
  SelectedItem weapon;
  SelectedItem armour;
  SelectedItem shield;
  ItemEquipType equip_type;
} GlobalGame;

typedef struct {
  GlobalAll all;
  GlobalMenu menu;
  GlobalGame game;
  GlobalCharacterCreation character_creation;
} Global;

extern Global global;

#endif/*__GLOBAL_H__*/
