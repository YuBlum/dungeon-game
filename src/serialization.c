#include "include/serialization.h"
#include "include/core.h"
#include "include/global.h"
#include "include/types.h"
#include <stdio.h>
#include <string.h>

typedef struct {
  u32 index, size;
} DataID;

static const DataID data_ids[] = {
  [CHARACTER_SHEET_NAME_SIZE]          = { 0x000, 0x004 },
  [CHARACTER_SHEET_NAME_BUFF]          = { 0x004, 0x010 },
  [CHARACTER_SHEET_CLASS]              = { 0x014, 0x004 },
  [CHARACTER_SHEET_ATTRIBUTE_AGI]      = { 0x018, 0x004 },
  [CHARACTER_SHEET_ATTRIBUTE_INT]      = { 0x01c, 0x004 },
  [CHARACTER_SHEET_ATTRIBUTE_PRE]      = { 0x020, 0x004 },
  [CHARACTER_SHEET_ATTRIBUTE_STR]      = { 0x024, 0x004 },
  [CHARACTER_SHEET_ATTRIBUTE_VIG]      = { 0x028, 0x004 },
  [CHARACTER_SHEET_LEVEL]              = { 0x02c, 0x004 },
  [CHARACTER_SHEET_EXPERIENCE]         = { 0x030, 0x004 },
  [CHARACTER_SHEET_ARMOUR_POINTS]      = { 0x034, 0x004 },
  [CHARACTER_SHEET_HIT_POINTS_MAX]     = { 0x038, 0x004 },
  [CHARACTER_SHEET_HIT_POINTS_CUR]     = { 0x03c, 0x004 },
  [CHARACTER_SHEET_FOOD_POINTS_MAX]    = { 0x040, 0x004 },
  [CHARACTER_SHEET_FOOD_POINTS_CUR]    = { 0x044, 0x004 },
  [CHARACTER_SHEET_ESSENCE_POINTS_MAX] = { 0x048, 0x004 },
  [CHARACTER_SHEET_ESSENCE_POINTS_CUR] = { 0x04c, 0x004 },
};
#if DEVMODE
_Static_assert(sizeof (data_ids) / sizeof (DataID) == SERIALIZATION_TYPE_LAST, "Not all serialization types handled");
#endif

#define SERIALIZATION_BUFFER_SIZE 0x050

static u8 serialization_buffer[SERIALIZATION_BUFFER_SIZE];
static char path[SAVE_PATH_SIZE];
static bool serializing = false;

bool
deserialize_from_slot_file(SerializationType type, u32 slot_id, void *dest) {
  snprintf(path, SAVE_PATH_SIZE, SAVE_PATH_FMT, slot_id);
  FILE *f = fopen(path, "rb");
  if (!f) return false;
#if DEVMODE
  fseek(f, 0, SEEK_END);
  usize file_size = ftell(f);
  if (file_size != SERIALIZATION_BUFFER_SIZE) ERROR("File '%s' is corrupted", path);
#endif
  fseek(f, data_ids[type].index, SEEK_SET);
  fread(dest, data_ids[type].size, 1, f);
  fclose(f);
  return true;
}

void
serialization_start(void) {
  serializing = true;
  snprintf(path, SAVE_PATH_SIZE, SAVE_PATH_FMT, global.all.save_slot);
  FILE *f = fopen(path, "rb");
  if (!f) return;
#if DEVMODE
  fseek(f, 0, SEEK_END);
  usize file_size = ftell(f);
  if (file_size != SERIALIZATION_BUFFER_SIZE) ERROR("File '%s' is corrupted", path);
  rewind(f);
#endif
  fread(serialization_buffer, 1, SERIALIZATION_BUFFER_SIZE, f);
  fclose(f);
}

void
serialize(SerializationType type, void *src) {
  memcpy(&serialization_buffer[data_ids[type].index], src, data_ids[type].size);
}

void
deserialize(SerializationType type, void *dest) {
  memcpy(dest, &serialization_buffer[data_ids[type].index], data_ids[type].size);
}

void
serialization_end(void) {
  if (!serializing) return;
  serializing = false;
  snprintf(path, SAVE_PATH_SIZE, SAVE_PATH_FMT, global.all.save_slot);
  FILE *f = fopen(path, "wb");
  fwrite(serialization_buffer, 1, SERIALIZATION_BUFFER_SIZE, f);
  fclose(f);
}
