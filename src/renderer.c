#include <glad/glad.h>
#include <stdio.h>
#include <string.h>
#include "include/core.h"

typedef u32 Shader;

static void
renderer_shader_load_specific(const char *name, GLenum type) {
  const char *type_str = type == GL_VERTEX_SHADER ? "vertex" : "fragment";
  //Shader shader = glCreateShader(type);
  /* load shader source */
  {
    usize shader_path_size = strlen(name) + strlen("res/shaders//.glsl") + strlen(type_str);
    char *shader_path = malloc(shader_path_size);
    snprintf(shader_path, shader_path_size, "res/shaders/%s/%s.glsl", name, type_str);
    INFO("%s", shader_path);
  }
}

void
renderer_create(void) {
  renderer_shader_load_specific("quad", GL_VERTEX_SHADER);
  renderer_shader_load_specific("quad", GL_FRAGMENT_SHADER);
}

void
renderer_update(void) {
  glClearColor(0.8f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
