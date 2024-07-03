#include "include/hashtable.h"
#include <stdlib.h>
#include <string.h>
#include "include/core.h"
#include "include/types.h"

typedef struct {
  const char *str;
  bool occupied;
} HTKey;

typedef struct Hashtable Hashtable;

typedef struct {
  Hashtable *ht;
} HTValuesHeader;

typedef struct Hashtable {
  usize capa;
  usize size;
  usize type;
  HTValuesHeader *values_header;
  void *values;
  HTKey *keys;
} Hashtable;

#define GET_HASHTABLE(HASHTABLE) (((HTValuesHeader *)HASHTABLE) - 1)->ht

/* http://www.cse.yorku.ca/~oz/hash.html */
static usize
hash(const char *str) {
  usize hash = 5381;
  i32 c;
  while ((c = *str++)) hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}

void *
hashtable_create(usize type) {
  Hashtable *ht = malloc(sizeof (Hashtable));
  ht->type = type;
  ht->size = 0;
  ht->capa = 17;
  ht->values_header = malloc(sizeof (HTValuesHeader) + type * ht->capa);
  ht->values_header->ht = ht;
  ht->values = ht->values_header + 1;
  ht->keys = malloc(sizeof (HTKey) * ht->capa);
  memset(ht->keys, 0, sizeof (HTKey) * ht->capa);
  return ht->values;
}

i32
__hashtable_insert(void **hashtable, const char *key, const char *file, u32 line) {
  Hashtable *ht = GET_HASHTABLE(*hashtable);
  /* rehash */
  if ((ht->size / (f32)ht->capa) >= 0.75f) {
    usize new_capa = ht->capa * 2;
    HTValuesHeader *new_values_header = malloc(sizeof (HTValuesHeader) + ht->type * new_capa);
    void *new_values = new_values_header + 1;
    HTKey *new_keys = malloc(sizeof (HTKey) * new_capa);
    new_values_header->ht = ht;
    memset(new_keys, 0, sizeof (HTKey) * new_capa);
    for (usize i = 0; i < ht->capa; i++) {
      if (!ht->keys[i].occupied) continue;
      usize index = hash(ht->keys[i].str) % new_capa;
      while (new_keys[index].occupied) {
        if (strcmp(new_keys[index].str, ht->keys[i].str) == 0) ERROR("%s:%u: unreachable", file, line);
        index = (index + 1) % new_capa;
      }
      new_keys[index].str = ht->keys[i].str;
      new_keys[index].occupied = true;
      memcpy(new_values + ht->type * index, ht->values + ht->type * i, ht->type);
    }
    free(ht->values_header);
    free(ht->keys);
    ht->values_header = new_values_header;
    ht->values = new_values;
    ht->keys = new_keys;
    ht->capa = new_capa;
    *hashtable = new_values;
  }
  /* add new value */
  usize index = hash(key) % ht->capa;
  while (ht->keys[index].occupied) {
    if (strcmp(ht->keys[index].str, key) == 0) ERROR("%s:%u: Adding '%s' two times to a hashtable", file, line, key);
    index = (index + 1) % ht->capa;
  }
  ht->keys[index].str = key;
  ht->keys[index].occupied = true;
  ht->size++;
  return index;
}

void
__hashtable_remove(void *hashtable, const char *key, const char *file, u32 line) {
  Hashtable *ht = GET_HASHTABLE(hashtable);
  usize index = hash(key) % ht->capa;
  bool finded = false;
  while (ht->keys[index].occupied) {
    if (strcmp(ht->keys[index].str, key) == 0) {
      finded = true;
      break;
    }
  }
  if (!finded) ERROR("%s:%u: Trying to remove an unexisting value '%s' of a hashtable", file, line, key);
  ht->keys[index].occupied = false;
  ht->size--;
}

i32
__hashtable_index(void *hashtable, const char *key, const char *file, u32 line) {
  Hashtable *ht = GET_HASHTABLE(hashtable);
  usize index = hash(key) % ht->capa;
  while (ht->keys[index].occupied) {
    if (strcmp(ht->keys[index].str, key) == 0) return index;
    index = (index + 1) % ht->capa;
  }
  ERROR("%s:%u: '%s' is not a key for this hashtable", file, line, key);
}

bool
__hashtable_has(void *hashtable, const char *key) {
  Hashtable *ht = GET_HASHTABLE(hashtable);
  usize index = hash(key) % ht->capa;
  while (ht->keys[index].occupied) {
    if (strcmp(ht->keys[index].str, key) == 0) return true;
    index = (index + 1) % ht->capa;
  }
  return false;
}

void
hashtable_destroy(void *hashtable) {
  Hashtable *ht = GET_HASHTABLE(hashtable);
  free(ht->keys);
  free(ht->values_header);
  free(ht);
}
