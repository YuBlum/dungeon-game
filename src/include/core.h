#ifndef __CORE_H__
#define __CORE_H__

#include <stdio.h>
#include <stdlib.h>

#define INFO(MSG, ...) printf("INFO: " MSG "\n", ## __VA_ARGS__)
#define WARN(MSG, ...) printf("WARN: " MSG "\n", ## __VA_ARGS__)
#define ERROR(MSG, ...) do { printf("ERROR: " MSG "\n", ## __VA_ARGS__); exit(1); } while(0)

#define GAME_TITLE    "Game"
#define UNIT_PX       8
#define GAME_W_PX     160
#define GAME_H_PX     90
#define GAME_W        (GAME_W_PX / (f32)UNIT_PX)
#define GAME_H        (GAME_H_PX / (f32)UNIT_PX)
#define WINDOW_SCALE  10
#define WINDOW_W      (GAME_W_PX * WINDOW_SCALE)
#define WINDOW_H      (GAME_H_PX * WINDOW_SCALE)

#endif/*__CORE_H__*/
