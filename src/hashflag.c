#include <stdlib.h>
#include <string.h>
#include <xxhash.h>
#include "include/hashflag.h"
#include "include/types.h"
#include "include/core.h"
#include "include/hash.h"

typedef struct {
  const char *str;
  bool occupied;
} Flag;

typedef struct HashFlag {
  usize capa;
  usize size;
  Flag *flags;
} HashFlag;

HashFlag *
hashflag_create(void) {
  HashFlag *hf = malloc(sizeof (HashFlag));
  hf->size = 0;
  hf->capa = 17;
  hf->flags = malloc(sizeof (Flag) * hf->capa);
  memset(hf->flags, 0, sizeof (Flag) * hf->capa);
  return hf;
}

void
__hashflag_set(HashFlag *hf, const char *flag, const char *file, u32 line) {
  /* rehash */
  if ((hf->size / (f32)hf->capa) >= 0.75f) {
    usize new_capa = hf->capa * 2;
    Flag *new_flags = malloc(sizeof (Flag) * new_capa);
    memset(new_flags, 0, sizeof (Flag) * new_capa);
    for (usize i = 0; i < hf->capa; i++) {
      if (!hf->flags[i].occupied) continue;
      usize index = hash_string(hf->flags[i].str) % new_capa;
      while (new_flags[index].occupied) {
#if DEVMODE
        if (strcmp(new_flags[index].str, hf->flags[i].str) == 0) ERROR("%s:%u: unreachable", file, line);
#endif
        index = (index + 1) % new_capa;
      }
      new_flags[index].str = hf->flags[i].str;
      new_flags[index].occupied = true;
    }
    free(hf->flags);
    hf->flags = new_flags;
    hf->capa = new_capa;
  }
  /* add new value */
  usize index = hash_string(flag) % hf->capa;
  while (hf->flags[index].occupied) {
#if DEVMODE
    if (strcmp(hf->flags[index].str, flag) == 0) ERROR("%s:%u: Setting '%s' two times to a hashflag", file, line, flag);
#endif
    index = (index + 1) % hf->capa;
  }
  hf->flags[index].str = flag;
  hf->flags[index].occupied = true;
  hf->size++;
}

void
__hashflag_clear(HashFlag *hf, const char *flag, const char *file, u32 line) {
  usize index = hash_string(flag) % hf->capa;
  bool finded = false;
  while (hf->flags[index].occupied) {
    if (strcmp(hf->flags[index].str, flag) == 0) { finded = true; break; }
    index = (index + 1) % hf->capa;
  }
#if DEVMODE
  if (!finded) ERROR("%s:%u: Trying to clear an unexisting flag '%s' of a hashflag", file, line, flag);
#endif
  hf->flags[index].occupied = false;
  hf->size--;
}

bool
hashflag_get(HashFlag *hf, const char *flag) {
  usize index = hash_string(flag) % hf->capa;
  while (hf->flags[index].occupied) {
    if (strcmp(hf->flags[index].str, flag) == 0) return true;
    index = (index + 1) % hf->capa;
  }
  return false;
}

void
hashflag_destroy(HashFlag *hf) {
  free(hf->flags);
  free(hf);
}
