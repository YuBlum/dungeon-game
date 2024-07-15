#ifndef __MATH_H__
#define __MATH_H__

#include <math.h>
#include "engine/types.h"

#define MIN(X, Y) (X < Y ? Y : X)
#define MAX(X, Y) (X > Y ? Y : X)
#define CLAMP(MN, MX, X) MIN(MN, MAX(MX, X))

static inline f32 lerp(f32 a, f32 b, f32 t) { return (1 - t) * a + t * b; }
static inline f32 smoothstep(f32 a, float b, float t) { t = CLAMP(0.0f, 1.0f, (t - a) / (b - a)); return t * t * (3.0f - 2.0f * t); }
static inline f32 parabola(f32 t, f32 k) { return pow( 4.0*t*(1.0-t), k ); }

typedef struct { f32 x, y; } V2f;
typedef struct { i32 x, y; } V2i;

#define V2F(X, Y) ((V2f) { X, Y })
#define V2FS(X)   ((V2f) { X, X })
#define V2FV(V)   ((V2f) { (V).x, (V).y })

#define V2I(X, Y) ((V2i) { X, Y })
#define V2IS(X)   ((V2i) { X, X })
#define V2IV(V)   ((V2i) { (V).x, (V).y })

static inline V2f v2f_add(V2f a, V2f b) { return V2F(a.x + b.x, a.y + b.y); }
static inline V2f v2f_sub(V2f a, V2f b) { return V2F(a.x - b.x, a.y - b.y); }
static inline V2f v2f_mul(V2f a, V2f b) { return V2F(a.x * b.x, a.y * b.y); }
static inline V2f v2f_div(V2f a, V2f b) { return V2F(a.x / b.x, a.y / b.y); }

static inline V2f v2f_adds(V2f a, f32 b) { return V2F(a.x + b, a.y + b); }
static inline V2f v2f_subs(V2f a, f32 b) { return V2F(a.x - b, a.y - b); }
static inline V2f v2f_muls(V2f a, f32 b) { return V2F(a.x * b, a.y * b); }
static inline V2f v2f_divs(V2f a, f32 b) { return V2F(a.x / b, a.y / b); }

static inline f32 v2f_mag2(V2f a) { return a.x*a.x + a.y*a.y; }
static inline f32 v2f_mag(V2f a) { return sqrtf(a.x*a.x + a.y*a.y); }
static inline f32 v2f_dot(V2f a, V2f b) { return a.x*b.x + a.y*b.y; }
static inline f32 v2f_dist(V2f a, V2f b) { return sqrtf((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y)); }
static inline f32 v2f_ang(V2f a) { return atan2(a.y, a.x); }
static inline f32 v2f_ang2(V2f a, V2f b) { return atan2(b.x-a.x, b.y-a.y); }

static inline V2f v2f_lerp(V2f a, V2f b, f32 t) { return V2F(lerp(a.x, b.x, t), lerp(a.y, b.y, t)); }

static inline V2i v2i_add(V2i a, V2i b) { return V2I(a.x + b.x, a.y + b.y); }
static inline V2i v2i_sub(V2i a, V2i b) { return V2I(a.x - b.x, a.y - b.y); }
static inline V2i v2i_mul(V2i a, V2i b) { return V2I(a.x * b.x, a.y * b.y); }
static inline V2i v2i_div(V2i a, V2i b) { return V2I(a.x / b.x, a.y / b.y); }

static inline V2i v2i_adds(V2i a, i32 b) { return V2I(a.x + b, a.y + b); }
static inline V2i v2i_subs(V2i a, i32 b) { return V2I(a.x - b, a.y - b); }
static inline V2i v2i_muls(V2i a, i32 b) { return V2I(a.x * b, a.y * b); }
static inline V2i v2i_divs(V2i a, i32 b) { return V2I(a.x / b, a.y / b); }

#endif/*__MATH_H__*/
