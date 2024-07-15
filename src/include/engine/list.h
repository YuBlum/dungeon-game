#ifndef __LIST_H__
#define __LIST_H__

#include "engine/types.h"

void *list_create(usize type);
void *__list_grow(void *list);
void  list_shrink(void *list);
void  list_shift_left(void *list, u32 index);
void  list_shift_right(void *list, u32 index);
void list_clear(void *list);
void  list_destroy(void *list);

#define list_capacity(LIST) (*(((usize *)(LIST)) - 3))
#define list_size(LIST) (*(((usize *)(LIST)) - 2))
#define list_grow(LIST) do { (LIST) = __list_grow(LIST); } while(0)
#define list_push(LIST, ITEM) do { (LIST) = __list_grow(LIST); (LIST)[list_size(LIST) - 1] = ITEM; } while(0)
#define list_pop(LIST) do { list_shrink(LIST); } while(0)
#define list_insert(LIST, INDEX, ITEM) do { (LIST) = __list_grow(LIST); list_shift_right(LIST, INDEX); (LIST)[INDEX] = ITEM; } while(0)
#define list_remove(LIST, INDEX) do { list_shift_left(LIST, INDEX); list_shrink(LIST); } while(0)
#define list_push_back(LIST, ITEM) list_insert(LIST, 0, ITEM)
#define list_pop_back(LIST) list_remove(LIST, 0)

#endif/*__LIST_H__*/
