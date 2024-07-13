#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "include/global.h"
#include "include/input.h"
#include "include/types.h"
#include "include/core.h"

#if DEVMODE
#define ERROR_GLFW(MSG) do {\
  const char *desc;\
  glfwGetError(&desc);\
  ERROR("GLFW: " MSG ": %s", desc);\
} while (0)
#endif

static GLFWwindow *window;
static f32 frame_start_time;

void
window_create(void) {
#if DEVMODE
  if (!glfwInit()) ERROR_GLFW("Couldn't initiate");
#else
  glfwInit();
#endif
  glfwWindowHint(GLFW_RESIZABLE, false);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if DEVMODE
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
  window = glfwCreateWindow(WINDOW_W, WINDOW_H, GAME_TITLE, 0, 0);
  const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  glfwSetWindowPos(window, (vidmode->width - WINDOW_W) >> 1, (vidmode->height - WINDOW_H) >> 1);
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glfwSetKeyCallback(window, (GLFWkeyfun)input_key_callback);
  glfwSetCharCallback(window, (GLFWcharfun)input_char_callback);
  global.all.dt = 1.0f/60.0f;
}

bool
window_is_running(void) {
  return !glfwWindowShouldClose(window);
}

void
window_frame_start(void) {
  frame_start_time = glfwGetTime();
}

void
window_frame_end(void) {
  glfwPollEvents();
  glfwSwapBuffers(window);
  global.all.dt = glfwGetTime() - frame_start_time;
}

void
window_destroy(void) {
  glfwSetWindowShouldClose(window, true);
}
