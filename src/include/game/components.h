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

typedef union {
  struct {
    i32 agility;
    i32 intelect;
    i32 presence;
    i32 strength;
    i32 vigor;
  };
  i32 arr[5];
} Attributes;

typedef struct {
  u32 hit_points_cur;
  u32 hit_points_max;
  u32 armour_points;
} DefensiveStats;

typedef struct {
  u32 carrying_weight_cur;
  u32 carrying_weight_max;
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
  bool wrap;
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

/*
 * item_type:
 *   item_melee
 *   item_ranged
 *   item_ammo
 *   item_staff
 *   item_potion
 *   item_component
 *   item_lockpick
 *
 * item_amount
 * item_weight
 * item_name
 * item_equiped
 *
 *
 */

typedef enum {
  ITEM_WOOD_SWORD = 0,
  ITEM_KNIFE,
  ITEM_DAGGER,
  ITEM_SHORTSWORD,
  ITEM_HANDAXE,
  ITEM_LONGSWORD,
  ITEM_TRIDANT,
  ITEM_WARHAMMER,
  ITEM_GREATSWORD,
  ITEM_BATTLEAXE,
  ITEM_MAUL,
  ITEM_DREAMSWORD,
  ITEM_MASTERSWORD,
  ITEM_GODS_WEAPON,
  ITEM_SLINGSHOT,
  ITEM_BIG_SLINGSHOT,
  ITEM_SMALL_THROWING_KNIFE,
  ITEM_SHORTBOW,
  ITEM_THROWING_KNIFE,
  ITEM_LIGHT_CROSSBOW,
  ITEM_HAND_CROSSBOW,
  ITEM_LONGBOW,
  ITEM_HUNTING_BOW,
  ITEM_HEAVY_CROSSBOW,
  ITEM_MASTERBOW,
  ITEM_KILLER_CROSSBOW,
  ITEM_SMALL_STAFF,
  ITEM_STAFF,
  ITEM_BIG_STAFF,
  ITEM_SMALL_SACRED_STAFF,
  ITEM_SACRED_STAFF,
  ITEM_ESSENCED_STAFF,
  ITEM_BLESSED_TRUNK,
  ITEM_EDEN_WOOD,
  ITEM_DARKNESS_CANE,
  ITEM_SPIRITS_GUIDANCE,
  ITEM_ROCK,
  ITEM_SMALL_ARROW,
  ITEM_ARROW,
  ITEM_LARGE_ARROW,
  ITEM_WOOD_SHIELD,
  ITEM_SMALL_METAL_SHIELD,
  ITEM_METAL_SHIELD,
  ITEM_STRONG_METAL_SHIELD,
  ITEM_TITANIUM_SHIELD,
  ITEM_LIGHT_ARMOUR,
  ITEM_WEAK_METAL_ARMOUR,
  ITEM_METAL_ARMOUR,
  ITEM_STRONG_METAL_ARMOUR,
  ITEM_TITANIUM_ARMOUR,
  ITEM_SLIME_FLUID,
  ITEM_SACRED_WOOD,
  ITEM_UNDEAD_MEAT,
  ITEM_SKULLWALKER_BONE,
  ITEM_HOLY_WATER,
  ITEM_ANIMAL_BLOOD,
  ITEM_HUMAN_BLOOD,
  ITEM_ANIMAL_ORGAN,
  ITEM_HUMAN_ORGAN,
  ITEM_LOCKPICK,
  ITEM_ADVANCED_LOCKPICK,
  ITEM_MAGICAL_LOCKPICK,
  ITEM_HEALING_POTION,
  ITEM_LARGE_HEALING_POTION,
  ITEM_GREAT_HEALING_POTION,
  ITEM_WILL_POTION,
  ITEM_LARGE_WILL_POTION,
  ITEM_GREAT_WILL_POTION,
} Item;

typedef enum {
  ITEM_TYPE_MELEE = 0,
  ITEM_TYPE_RANGED,
  ITEM_TYPE_STAFF,
  ITEM_TYPE_DEFENSIVE,
  ITEM_TYPE_POTION,
  ITEM_TYPE_AMMO,
  ITEM_TYPE_LOCKPICK,
  ITEM_TYPE_MAGIC_COMPONENT,

  ITEM_TYPE_AMOUNT
} ItemType;

#define ITEM_NAME_CAP 24
typedef struct {
  char name_buff[ITEM_NAME_CAP];
  u32  name_size;
  u32  weight;
  u32  id;
  ItemType type;
} ItemInfo;

typedef enum {
  AMMO_NONE = 0,
  AMMO_ROCK,
  AMMO_SMALL_ARROW,
  AMMO_ARROW,
  AMMO_LARGE_ARROW
} AmmoType;

typedef enum {
  LOCKPICK_REGULAR,
  LOCKPICK_ADVANCED,
  LOCKPICK_MAGICAL
} LockpickType;

typedef enum {
  POTION_HEALING,
  POTION_WILL
} PotionType;

typedef enum {
  DEF_SHIELD,
  DEF_ARMOUR
} DefensiveType;

typedef struct {
  DefensiveType type;
  u32 extra_armour_points;
} DefensiveItem;

typedef enum {
  MAGIC_SLIME_FLUID,
  MAGIC_SACRED_WOOD,
  MAGIC_UNDEAD_MEAT,
  MAGIC_SKULLWALKER_BONE,
  MAGIC_HOLY_WATER,
  MAGIC_ANIMAL_BLOOD,
  MAGIC_HUMAN_BLOOD,
  MAGIC_ANIMAL_ORGAN,
  MAGIC_HUMAN_ORGAN
} MagicComponentType;

typedef enum {
  SPELL_REGULAR,
  SPELL_COMPLEX,
  SPELL_EXTREME
} SpellType;

typedef struct {
  SpellType spell_type;
  u32 reduce_dt;
} Staff;

typedef struct {
  u32 min;
  u32 mid;
  u32 max;
} ItemPriceRange;

typedef struct {
  u32 amount;
  u32 faces;
  u32 add;
} DiceTest;

void components_create(void);

#endif/*__COMPONENTS_H__*/
