#ifndef __STRING_H__
#define __STRING_H__

#include "include/types.h"
#include <string.h>

typedef struct {
  char *buff;
  usize size;
} String;

#define STRING(S) ((String) { S, sizeof (S) - 1 })

static inline bool string_compare(const String *s1, const String *s2) { return s1->size == s2->size && strncmp(s1->buff, s2->buff, s1->size) == 0; }
static inline bool string_cstring_compare(const String *s1, const char *s2) { return s1->size == strlen(s2) && strncmp(s1->buff, s2, s1->size) == 0; }

#endif/*__STRING_H__*/
