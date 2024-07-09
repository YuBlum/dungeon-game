#include "include/camera.h"
#include "include/core.h"
#include "include/types.h"

static const f32 game_projection[3][3] = {
  { 2.0f/(GAME_RIGHT - GAME_LEFT), 0                            , -(GAME_RIGHT + GAME_LEFT)/(GAME_RIGHT - GAME_LEFT) },
  { 0                            , 2.0f/(GAME_TOP - GAME_BOTTOM), -(GAME_TOP + GAME_BOTTOM)/(GAME_TOP - GAME_BOTTOM) },
  { 0                            , 0                            , 1                                                  },
};

static const f32 ui_projection[3][3] = {
  { 2.0f/(UI_RIGHT - UI_LEFT), 0                        , -(UI_RIGHT + UI_LEFT)/(UI_RIGHT - UI_LEFT) },
  { 0                        , 2.0f/(UI_TOP - UI_BOTTOM), -(UI_TOP + UI_BOTTOM)/(UI_TOP - UI_BOTTOM) },
  { 0                        , 0                        , 1                                          },
};

Camera
camera_game_matrix(void) {
  return (Camera)game_projection;
}

Camera
camera_ui_matrix(void) {
  return (Camera)ui_projection;
}
