#include "include/camera.h"
#include "include/core.h"
#include "include/types.h"

#define LEFT   -(GAME_W * 0.5f)
#define RIGHT  +(GAME_W * 0.5f)
#define BOTTOM -(GAME_H * 0.5f)
#define TOP    +(GAME_H * 0.5f)

static const f32 projection[3][3] = {
  { 2.0f/(RIGHT - LEFT),                   0, -(RIGHT + LEFT)/(RIGHT - LEFT) },
  {                   0, 2.0f/(TOP - BOTTOM), -(TOP + BOTTOM)/(TOP - BOTTOM) },
  {                   0,                   0,                              1 },
};

Camera
camera_matrix(void) {
  return (Camera)projection;
}
