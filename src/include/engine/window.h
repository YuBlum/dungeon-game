#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "general/types.h"

void window_create(void);
bool window_is_running(void);
void window_frame_start(void);
void window_frame_end(void);
void window_destroy(void);

#endif/*__WINDOW_H__*/
