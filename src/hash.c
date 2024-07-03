#include <string.h>
#include <xxhash.h>
#include "include/hash.h"

u64
hash_string(const char *str) {
  return XXH3_64bits(str, strlen(str));
}
