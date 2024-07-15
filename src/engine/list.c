#include <stdlib.h>
#include <string.h>
#include "engine/types.h"

typedef struct {
  usize capa;
  usize size;
  usize type;
} ListHeader;

#define LIST_HEADER(LIST) ((ListHeader *)((LIST) - sizeof (ListHeader)))

void *
list_create(usize type) {
  ListHeader *header = malloc(sizeof (ListHeader) + type);
  header->capa = 1;
  header->size = 0;
  header->type = type;
  return header + 1;
}

void *
__list_grow(void *list) {
  ListHeader *header = LIST_HEADER(list);
  if (header->size >= header->capa) {
    header->capa *= 2;
    header = realloc(header, sizeof (ListHeader) + header->type * header->capa);
  }
  header->size++;
  return header + 1;
}

void
list_shrink(void *list) {
  ListHeader *header = LIST_HEADER(list);
  if (header->size > 0) header->size--;
}

void
list_shift_left(void *list, u32 index) {
  ListHeader *header = LIST_HEADER(list);
  if (header->size <= 1) return;
  memmove(list + (index + 0) * header->type,
          list + (index + 1) * header->type,
          (header->size - index) * header->type);
}

void
list_shift_right(void *list, u32 index) {
  ListHeader *header = LIST_HEADER(list);
  if (header->size <= 1) return;
  if (index >= header->size - 1) return;
  memmove(list + (index + 1) * header->type,
          list + (index + 0) * header->type,
          (header->size - index - 1) * header->type);
}

void
list_clear(void *list) {
  LIST_HEADER(list)->size = 0;
}

void
list_destroy(void *list) {
  free(LIST_HEADER(list));
}
