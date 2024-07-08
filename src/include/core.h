#ifndef __CORE_H__
#define __CORE_H__

#include <stdio.h>
#include <stdlib.h>

#if DEVMODE
#  define INFO(MSG, ...) printf("INFO: " MSG "\n", ## __VA_ARGS__)
#  define WARN(MSG, ...) printf("WARN: " MSG "\n", ## __VA_ARGS__)
#  define ERROR(MSG, ...) do { printf("ERROR: " MSG "\n", ## __VA_ARGS__); exit(1); } while(0)
#else
#  define INFO(MSG, ...)
#  define WARN(MSG, ...)
#  define ERROR(MSG, ...)
#endif

#define GAME_TITLE    "Game"
#define UNIT_TO_PX       8
#define PX_TO_UNIT       (1.0f/UNIT_TO_PX)
#define GAME_W_PX     240
#define GAME_H_PX     135
#define GAME_W        (GAME_W_PX / (f32)UNIT_TO_PX)
#define GAME_H        (GAME_H_PX / (f32)UNIT_TO_PX)
#define WINDOW_SCALE  8
#define WINDOW_W      (GAME_W_PX * WINDOW_SCALE)
#define WINDOW_H      (GAME_H_PX * WINDOW_SCALE)

#endif/*__CORE_H__*/
