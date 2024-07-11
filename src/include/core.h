#ifndef __CORE_H__
#define __CORE_H__

#include "include/renderer.h"
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

#define GAME_W_PX       176
#define GAME_H_PX       178
#define GAME_BORDER_PX  1
#define GAME_Y_PX      GAME_BORDER_PX 
#define GAME_X_PX      GAME_BORDER_PX
#define UI_W_PX        (WINDOW_ORIGINAL_W - GAME_W_PX - GAME_BORDER_PX * 3)
#define UI_H_PX        GAME_H_PX
#define UI_X_PX        (GAME_BORDER_PX * 2 + GAME_W_PX)
#define UI_Y_PX        GAME_BORDER_PX

#define GAME_RIGHT  +(GAME_W / 2.0f)
#define GAME_LEFT   -(GAME_W / 2.0f)
#define GAME_TOP    +(GAME_H / 2.0f)
#define GAME_BOTTOM -(GAME_H / 2.0f)

#define UI_RIGHT  +(UI_W / 2.0f)
#define UI_LEFT   -(UI_W / 2.0f)
#define UI_TOP    +(UI_H / 2.0f)
#define UI_BOTTOM -(UI_H / 2.0f)

#define GAME_W (GAME_W_PX / (f32)UNIT_TO_PX)
#define GAME_H (GAME_H_PX / (f32)UNIT_TO_PX)
#define UI_W   (UI_W_PX / (f32)UNIT_TO_PX)
#define UI_H   (UI_H_PX / (f32)UNIT_TO_PX)

#define BORDER_COLOR ((Color)0xffffffff)

#endif/*__CORE_H__*/
