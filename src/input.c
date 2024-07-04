#include "include/input.h"
#include "include/types.h"
#include <GLFW/glfw3.h>
#include <string.h>

static bool key_down_cur[KEY_CAP];
static bool key_down_prv[KEY_CAP];
static bool key_up_cur[KEY_CAP];
static bool key_up_prv[KEY_CAP];

static i32 key_to_glfw_key[] = {
  [KEY_LEFT]   =  GLFW_KEY_LEFT,
  [KEY_RIGHT]  =  GLFW_KEY_RIGHT,
  [KEY_UP]     =  GLFW_KEY_UP,
  [KEY_DOWN]   =  GLFW_KEY_DOWN,
  [KEY_A]      =  GLFW_KEY_Z,
  [KEY_B]      =  GLFW_KEY_X,
};
_Static_assert(KEY_CAP == 6, "Not all keys are handled.");

void
input_key_callback(void* window, int glfw_key, int scancode, int action, int mods) {
  (void)window; (void)scancode; (void)mods;
  if (action != GLFW_PRESS && action != GLFW_RELEASE) return;
  for (Key key = 0; key < KEY_CAP; key++) {
    if (key_to_glfw_key[key] != glfw_key) continue;
    key_down_cur[key] = action == GLFW_PRESS;
    key_up_cur[key]   = action == GLFW_RELEASE;
  }
}

void
input_update(void) {
  memcpy(key_down_prv, key_down_cur, sizeof (bool) * KEY_CAP);
  memcpy(key_up_prv, key_up_cur, sizeof (bool) * KEY_CAP);
}

bool
input_key_down(Key key) {
  return key_down_cur[key];
}

bool
input_key_pressed(Key key) {
  return !key_down_prv[key] && key_down_cur[key];
}

bool
input_key_up(Key key) {
  return key_up_cur[key];
}

bool
input_key_released(Key key) {
  return !key_up_prv[key] && key_up_cur[key];
}
