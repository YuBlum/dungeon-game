#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "include/math.h"
#include "include/types.h"

typedef i32 Layer;

typedef u32 Color;
#define C_WHITE   0xFFFFFFFF
#define C_RED     0xFF0000FF
#define C_GREEN   0x00FF00FF
#define C_BLUE    0x0000FFFF
#define C_BLACK   0x000000FF
#define C_YELLOW  0xFFFF00FF
#define C_MAGENTA 0xFF00FFFF

void renderer_create(void);

void __renderer_rect(V2f position, V2f size, Color color, Layer layer, const char *file, u32 line);
#define renderer_rect(POSITION, SIZE, COLOR, LAYER) __renderer_rect(POSITION, SIZE, COLOR, LAYER, __FILE__, __LINE__)

void renderer_batch_start(void);
void renderer_batch_end(void);


#endif/*__RENDERER_H__*/
