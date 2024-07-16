#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

#include "engine/math.h"
#include "engine/types.h"

typedef const char *Tag;

typedef void *CallbackArg;

typedef void(*Callback)(void *);

typedef enum {
  CLASS_UNKNOWN = -1,
  CLASS_FIGHTER,
  CLASS_THIEF,
  CLASS_WIZARD
} Class;

typedef enum {
  ATT_AGILITY = 0,
  ATT_INTELECT,
  ATT_PRESENCE,
  ATT_STRENGTH,
  ATT_VIGOR
} AttributeType;

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

typedef struct {
  u32 essence_points_cur;
  u32 essence_points_max;
  u32 food_points_cur;
  u32 food_points_max;
  u32 experience;
  u32 level;
  u32 gold;
} CharacterSheet;

#define CHARACTER_NAME_CAP 8
typedef struct {
  char buff[CHARACTER_NAME_CAP];
  u32 size;
} CharacterName;

typedef struct {
  V2f prv;
  V2f nxt;
  f32 timer;
} PositionLerp;

typedef struct {
  bool horizontal;
} Cursor;

#define TERMINAL_LINE_CAP 11
#define TERMINAL_LINE_STR_CAP 21
typedef struct {
  u32  line;
  u32  line_cursor;
  char line_buff[TERMINAL_LINE_CAP][TERMINAL_LINE_STR_CAP];
  u32  line_size[TERMINAL_LINE_CAP];
} Terminal;

typedef enum {
  IGM_NONE = 0,
  IGM_PAUSE,
  IGM_INVENTORY,
  IGM_ABILITIES,
  IGM_SPELLS
} InGameMenuType;

void components_create(void);

#endif/*__COMPONENTS_H__*/
