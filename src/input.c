#include "include/input.h"
#include "include/core.h"
#include "include/types.h"
#include <GLFW/glfw3.h>
#include <string.h>

static bool key_down_cur[KEY_CAP];
static bool key_down_prv[KEY_CAP];
static bool key_up_cur[KEY_CAP];
static bool key_up_prv[KEY_CAP];
static bool key_repeat[KEY_CAP];

static i32 key_to_glfw_key[] = {
  [KEY_LEFT]      =  GLFW_KEY_LEFT,
  [KEY_RIGHT]     =  GLFW_KEY_RIGHT,
  [KEY_UP]        =  GLFW_KEY_UP,
  [KEY_DOWN]      =  GLFW_KEY_DOWN,
  [KEY_A]         =  GLFW_KEY_Z,
  [KEY_B]         =  GLFW_KEY_X,
  [KEY_BACKSPACE] =  GLFW_KEY_BACKSPACE,
};
#if DEVMODE
_Static_assert(KEY_CAP == 7, "Not all keys are handled.");
#endif

static char letter_pressed;

void
input_key_callback(void *window, int glfw_key, int scancode, int action, int mods) {
  (void)window; (void)scancode; (void)mods;
  for (Key key = 0; key < KEY_CAP; key++) {
    if (key_to_glfw_key[key] != glfw_key) continue;
    key_down_cur[key] = action == GLFW_PRESS;
    key_up_cur[key]   = action == GLFW_RELEASE;
    key_repeat[key]   = action == GLFW_REPEAT;
  }
}

void
input_char_callback(void *window, u32 codepoint) {
  (void)window;
  if (codepoint == ' ' || (codepoint >= 'A' && codepoint <= 'Z') || (codepoint >= 'a' && codepoint <= 'z'))
    letter_pressed = codepoint;
}

void
input_update(void) {
  memcpy(key_down_prv, key_down_cur, sizeof (bool) * KEY_CAP);
  memcpy(key_up_prv, key_up_cur, sizeof (bool) * KEY_CAP);
  memset(key_repeat, 0, sizeof (bool) * KEY_CAP);
  letter_pressed = -1;
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

bool
input_key_repeated(Key key) {
  return (!key_down_prv[key] && key_down_cur[key]) || key_repeat[key];
}

char
input_letter_pressed(void) {
  return letter_pressed;
}
