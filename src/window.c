#include "include/core.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
}

bool
window_is_running(void) {
  return !glfwWindowShouldClose(window);
}

void
window_frame_start(void) {
  glfwPollEvents();
}

void
window_frame_end(void) {
  glfwSwapBuffers(window);
}
