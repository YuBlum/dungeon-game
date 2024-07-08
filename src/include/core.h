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

#define WINDOW_SCALE      6
#define WINDOW_ORIGINAL_W 320
#define WINDOW_ORIGINAL_H 180
#define WINDOW_W          (WINDOW_ORIGINAL_W * WINDOW_SCALE)
#define WINDOW_H          (WINDOW_ORIGINAL_H * WINDOW_SCALE)

#define GAME_TITLE "Game"
#define UNIT_TO_PX 8
#define PX_TO_UNIT (1.0f/UNIT_TO_PX)

#define GAME_W_PX 176
#define GAME_H_PX 176
#define GAME_Y_PX (((WINDOW_ORIGINAL_H - GAME_H_PX) >> 1) * WINDOW_SCALE)
#define GAME_X_PX GAME_Y_PX
#define GAME_W    (GAME_W_PX / (f32)UNIT_TO_PX)
#define GAME_H    (GAME_H_PX / (f32)UNIT_TO_PX)

#endif/*__CORE_H__*/
