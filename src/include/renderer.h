#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "include/math.h"
#include "include/types.h"

typedef i32 Layer;

typedef u32 Color;

#define COLOR_R(COLOR) ((COLOR >> 24) & 0xFF)
#define COLOR_G(COLOR) ((COLOR >> 16) & 0xFF)
#define COLOR_B(COLOR) ((COLOR >>  8) & 0xFF)
#define COLOR_A(COLOR) ((COLOR >>  0) & 0xFF)

#define COLOR_NR(COLOR) (((COLOR >> 24) & 0xFF) / 255.0f)
#define COLOR_NG(COLOR) (((COLOR >> 16) & 0xFF) / 255.0f)
#define COLOR_NB(COLOR) (((COLOR >>  8) & 0xFF) / 255.0f)
#define COLOR_NA(COLOR) (((COLOR >>  0) & 0xFF) / 255.0f)

typedef enum {
  RENDER_UI = 0,
  RENDER_GAME,

  RENDER_TARGET_AMOUNT
} RenderTarget;

void renderer_create(void);


void __renderer_rect(V2f position, V2f size, bool center, f32 r, f32 g, f32 b, f32 a, Layer layer, const char *file, u32 line);
void __renderer_clear(f32 r, f32 g, f32 b);
void __renderer_text(V2f position, f32 scale, bool center, f32 r, f32 g, f32 b, f32 a, Layer layer, const char *file, u32 line, const char *fmt, ...);
V2f renderer_text_dimensions(f32 scale, const char *fmt, ...);
void renderer_batch_start(RenderTarget target);
void renderer_batch_end(RenderTarget target);

#define renderer_rect(POSITION, SIZE, CENTER, COLOR, LAYER) __renderer_rect(POSITION, SIZE, CENTER, COLOR_NR(COLOR), COLOR_NG(COLOR), COLOR_NB(COLOR), COLOR_NA(COLOR), LAYER, __FILE__, __LINE__)
#define renderer_text(POSITION, SCALE, CENTER, COLOR, LAYER, FMT, ...) __renderer_text(POSITION, SCALE, CENTER, COLOR_NR(COLOR), COLOR_NG(COLOR), COLOR_NB(COLOR), COLOR_NA(COLOR), LAYER, __FILE__, __LINE__, FMT, ## __VA_ARGS__)
#define renderer_clear(COLOR) __renderer_clear(COLOR_NR(COLOR), COLOR_NG(COLOR), COLOR_NB(COLOR))

#endif/*__RENDERER_H__*/
