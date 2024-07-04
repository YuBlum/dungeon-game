#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "include/input.h"
#include "include/types.h"
#include "include/core.h"

#define ERROR_GLFW(MSG) do {\
  const char *desc;\
  glfwGetError(&desc);\
  ERROR("GLFW: " MSG ": %s", desc);\
} while (0)

static GLFWwindow *window;


void
window_create(void) {
  if (!glfwInit()) ERROR_GLFW("Couldn't initiate");
  glfwWindowHint(GLFW_RESIZABLE, false);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  window = glfwCreateWindow(WINDOW_W, WINDOW_H, GAME_TITLE, 0, 0);
  const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  glfwSetWindowPos(window, (vidmode->width * 0.5f) - (WINDOW_W * 0.5f), (vidmode->height * 0.5f) - (WINDOW_H * 0.5f));
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glfwSetKeyCallback(window, (GLFWkeyfun)input_key_callback);
}

bool
window_is_running(void) {
  return !glfwWindowShouldClose(window);
}

void
window_frame_start(void) {
}

void
window_frame_end(void) {
  glfwPollEvents();
  glfwSwapBuffers(window);
}

void
window_destroy(void) {
  glfwSetWindowShouldClose(window, true);
}
