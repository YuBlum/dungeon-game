#include "include/camera.h"
#include "include/core.h"
#include "include/types.h"

#define RIGHT  +(GAME_W / 2.0f)
#define LEFT   -(GAME_W / 2.0f)
#define TOP    +(GAME_H / 2.0f)
#define BOTTOM -(GAME_H / 2.0f)

static const f32 projection[3][3] = {
  { 2.0f/(RIGHT - LEFT), 0                  , -(RIGHT + LEFT)/(RIGHT - LEFT) },
  { 0                  , 2.0f/(TOP - BOTTOM), -(TOP + BOTTOM)/(TOP - BOTTOM) },
  { 0                  , 0                  , 1                              },
};

/*
static const f32 projection[3][3] = {
  { 1, 0, 0 },
  { 0, 1, 0 },
  { 0, 0, 1 },
};
*/

Camera
camera_matrix(void) {
  return (Camera)projection;
}
