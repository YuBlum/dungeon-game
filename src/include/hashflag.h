#ifndef __HASHFLAG_H__
#define __HASHFLAG_H__

#include "include/types.h"

typedef struct HashFlag HashFlag;

HashFlag *hashflag_create(void);
void  __hashflag_set(HashFlag *hashflag, const char *flag, const char *file, u32 line);
void __hashflag_clear(HashFlag *hashflag, const char *flag, const char *file, u32 line);
bool hashflag_get(HashFlag *hashflag, const char *flag);
void hashflag_destroy(HashFlag *hashflag);

#define hashflag_set(HASHFLAG, FLAG) __hashflag_set(HASHFLAG, FLAG, __FILE__, __LINE__)
#define hashflag_clear(HASHFLAG, FLAG) __hashflag_clear(HASHFLAG, FLAG, __FILE__, __LINE__)

#endif/*__HASHFLAG_H__*/
