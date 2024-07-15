#ifndef __SERIALIZATION_H__
#define __SERIALIZATION_H__

#include "engine/types.h"
typedef enum {
  CHARACTER_SHEET_NAME_SIZE,
  CHARACTER_SHEET_NAME_BUFF,
  CHARACTER_SHEET_CLASS,
  CHARACTER_SHEET_ATTRIBUTE_AGI,
  CHARACTER_SHEET_ATTRIBUTE_INT,
  CHARACTER_SHEET_ATTRIBUTE_PRE,
  CHARACTER_SHEET_ATTRIBUTE_STR,
  CHARACTER_SHEET_ATTRIBUTE_VIG,
  CHARACTER_SHEET_GOLD,
  CHARACTER_SHEET_LEVEL,
  CHARACTER_SHEET_EXPERIENCE,
  CHARACTER_SHEET_ARMOUR_POINTS,
  CHARACTER_SHEET_HIT_POINTS_MAX,
  CHARACTER_SHEET_HIT_POINTS_CUR,
  CHARACTER_SHEET_FOOD_POINTS_MAX,
  CHARACTER_SHEET_FOOD_POINTS_CUR,
  CHARACTER_SHEET_ESSENCE_POINTS_MAX,
  CHARACTER_SHEET_ESSENCE_POINTS_CUR,

  SERIALIZATION_TYPE_LAST
} SerializationType;

bool deserialize_from_slot_file(SerializationType type, u32 slot_id, void *dest);
void serialization_start(void);
void serialize(SerializationType type, void *src);
void deserialize(SerializationType type, void *dest);
void serialization_end(void);

#endif/*__SERIALIZATION_H__*/
