#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include "engine/types.h"

void *hashtable_create(usize type);
i32  __hashtable_insert(void **hashtable, const char *key, const char *file, u32 line);
void __hashtable_remove(void *hashtable, const char *key, const char *file, u32 line);
i32  __hashtable_index(void *hashtable, const char *key, const char *file, u32 line);
bool __hashtable_has(void *hashtable, const char *key);
void hashtable_destroy(void *hashtable);

#define hashtable_insert(HASHTABLE, KEY, ITEM) do { i32 index = __hashtable_insert((void **)&HASHTABLE, KEY, __FILE__, __LINE__); HASHTABLE[index] = ITEM; } while(0)
#define hashtable_remove(HASHTABLE, KEY) __hashtable_remove(HASHTABLE, KEY, __FILE__, __LINE__)
#define hashtable_set(HASHTABLE, KEY, ITEM) do { HASHTABLE[__hashtable_index(HASHTABLE, KEY, __FILE__, __LINE__)] = ITEM; } while(0)
#define hashtable_get(HASHTABLE, KEY) (HASHTABLE[__hashtable_index(HASHTABLE, KEY, __FILE__, __LINE__)])
#define hashtable_get_address(HASHTABLE, KEY) (&HASHTABLE[__hashtable_index(HASHTABLE, KEY, __FILE__, __LINE__)])
#define hashtable_has(HASHTABLE, KEY) __hashtable_has(HASHTABLE, KEY)

#endif/*__HASHTABLE_H__*/
