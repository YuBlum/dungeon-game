#ifndef __MATH_H__
#define __MATH_H__

#include <math.h>
#include "include/types.h"

typedef struct { f32 x, y; } V2f;

#define V2F(X, Y) ((V2f) { X, Y })
#define V2S(X)    ((V2f) { X, X })

static inline V2f v2_add(V2f a, V2f b) { return V2F(a.x + b.x, a.y + b.y); }
static inline V2f v2_sub(V2f a, V2f b) { return V2F(a.x - b.x, a.y - b.y); }
static inline V2f v2_mul(V2f a, V2f b) { return V2F(a.x * b.x, a.y * b.y); }
static inline V2f v2_div(V2f a, V2f b) { return V2F(a.x / b.x, a.y / b.y); }

static inline V2f v2_adds(V2f a, f32 b) { return V2F(a.x + b, a.y + b); }
static inline V2f v2_subs(V2f a, f32 b) { return V2F(a.x - b, a.y - b); }
static inline V2f v2_muls(V2f a, f32 b) { return V2F(a.x * b, a.y * b); }
static inline V2f v2_divs(V2f a, f32 b) { return V2F(a.x / b, a.y / b); }

static inline f32 v2_mag2(V2f a) { return a.x*a.x + a.y*a.y; }
static inline f32 v2_mag(V2f a) { return sqrtf(a.x*a.x + a.y*a.y); }
static inline f32 v2_dot(V2f a, V2f b) { return a.x*b.x + a.y*b.y; }
static inline f32 v2_dist(V2f a, V2f b) { return sqrtf((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y)); }
static inline f32 v2_ang(V2f a) { return atan2(a.y, a.x); }
static inline f32 v2_ang2(V2f a, V2f b) { return atan2(b.x-a.x, b.y-a.y); }

#endif/*__MATH_H__*/
