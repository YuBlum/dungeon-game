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

#define COLOR_R(COLOR) ((COLOR >> 24) & 0xFF)
#define COLOR_G(COLOR) ((COLOR >> 16) & 0xFF)
#define COLOR_B(COLOR) ((COLOR >>  8) & 0xFF)
#define COLOR_A(COLOR) ((COLOR >>  0) & 0xFF)

#define COLOR_NR(COLOR) (((COLOR >> 24) & 0xFF) / 255.0f)
#define COLOR_NG(COLOR) (((COLOR >> 16) & 0xFF) / 255.0f)
#define COLOR_NB(COLOR) (((COLOR >>  8) & 0xFF) / 255.0f)
#define COLOR_NA(COLOR) (((COLOR >>  0) & 0xFF) / 255.0f)

void renderer_create(void);

void __renderer_rect(V2f position, V2f size, f32 r, f32 g, f32 b, f32 a, Layer layer, const char *file, u32 line);
#define renderer_rect(POSITION, SIZE, COLOR, LAYER) __renderer_rect(POSITION, SIZE, COLOR_NR(COLOR), COLOR_NG(COLOR), COLOR_NB(COLOR), COLOR_NA(COLOR), LAYER, __FILE__, __LINE__)

void __renderer_text(V2f position, f32 scale, f32 r, f32 g, f32 b, f32 a, Layer layer, const char *file, u32 line, const char *fmt, ...);
#define renderer_text(POSITION, SCALE, COLOR, LAYER, FMT, ...) __renderer_text(POSITION, SCALE, COLOR_NR(COLOR), COLOR_NG(COLOR), COLOR_NB(COLOR), COLOR_NA(COLOR), LAYER, __FILE__, __LINE__, FMT, ## __VA_ARGS__)

void renderer_batch_start(void);
void renderer_batch_end(void);


#endif/*__RENDERER_H__*/
