#ifndef __INPUT_H__
#define __INPUT_H__

#include "engine/types.h"
typedef enum {
  KEY_LEFT = 0,
  KEY_RIGHT,
  KEY_UP,
  KEY_DOWN,
  KEY_A,
  KEY_B,
  KEY_BACKSPACE,
  KEY_ESC,

  KEY_CAP
} Key;

void input_key_callback(void* window, int key, int scancode, int action, int mods);
void input_char_callback(void *window, u32 codepoint);
void input_update(void);
bool input_key_down(Key key);
bool input_key_pressed(Key key);
bool input_key_up(Key key);
bool input_key_released(Key key);
bool input_key_repeated(Key key);
char input_letter_pressed(void);

#endif/*__INPUT_H__*/
