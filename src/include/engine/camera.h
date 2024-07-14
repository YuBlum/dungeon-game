#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "general/types.h"
typedef f32 *Camera;

typedef Camera (*CameraProjFn)(void);

Camera camera_screen_matrix(void);
Camera camera_game_matrix(void);
Camera camera_ui_matrix(void);

#endif/*__CAMERA_H__*/
