#include <errno.h>
#include <glad/glad.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "include/core.h"

#define QUADS_CAP    10000
#define VERTICES_CAP (QUADS_CAP * 4)
#define INDICES_CAP  (QUADS_CAP * 6)

typedef u32 Shader, Object;

typedef struct {
  struct {
    f32 x, y;
  } position;
} Vertex;

static Shader sh_quad;

static Object vertex_array;
static Object vertex_buffer;
static Object index_buffer;

static Vertex vertices[VERTICES_CAP] = {
  { { -0.5f, -0.5f } },
  { { +0.5f, -0.5f } },
  { { +0.5f, +0.5f } },
  { { -0.5f, +0.5f } },
};

static Shader
renderer_shader_load_specific(const char *name, GLenum type) {
  const char *type_str = type == GL_VERTEX_SHADER ? "vertex" : "fragment";
  Shader shader = glCreateShader(type);
  /* load source */
  usize shader_path_size = strlen(name) + strlen("res/shaders//.glsl") + strlen(type_str) + 1;
  char *shader_path = malloc(shader_path_size);
  snprintf(shader_path, shader_path_size, "res/shaders/%s/%s.glsl", name, type_str);
  FILE *f = fopen(shader_path, "r");
  if (!f) ERROR("Couldn't open '%s': %s", shader_path, strerror(errno));
  free(shader_path);
  fseek(f, 0, SEEK_END);
  usize src_size = ftell(f);
  fseek(f, 0, SEEK_SET);
  char *src = malloc(src_size + 1);
  fread(src, 1, src_size, f);
  src[src_size] = 0;
  fclose(f);
  glShaderSource(shader, 1, (const char **)&src, 0);
  free(src);
  /* compile */
  i32 status;
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (!status) {
    i32 log_size;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
    char *log = malloc(log_size);
    glGetShaderInfoLog(shader, log_size, 0, log);
    ERROR("Shader '%s': %s: %.*s", name, type_str, log_size, log);
  }
  return shader;
}

static Shader
renderer_shader_load(const char *name) {
  Shader shader = glCreateProgram();
  Shader vertex = renderer_shader_load_specific(name, GL_VERTEX_SHADER);
  Shader fragment = renderer_shader_load_specific(name, GL_FRAGMENT_SHADER);
  /* link shaders */
  i32 status;
  glAttachShader(shader, vertex);
  glAttachShader(shader, fragment);
  glLinkProgram(shader);
  glDeleteShader(vertex);
  glDeleteShader(fragment);
  glGetProgramiv(shader, GL_LINK_STATUS, &status);
  if (!status) {
     i32 log_size;
     glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &log_size);
     char *log = malloc(log_size);
     glGetProgramInfoLog(shader, log_size, 0, log);
     ERROR("Shader '%s': linking: %.*s", name, log_size, log);
  }
  return shader;
}

void
renderer_create(void) {
  /* shaders */
  sh_quad = renderer_shader_load("quad");
  glUseProgram(sh_quad);
  /* indices setup */
  u32 indices[INDICES_CAP];
  {
    u32 i = 0, j = 0;
    while (i < INDICES_CAP) {
      indices[i++] = j + 0;
      indices[i++] = j + 1;
      indices[i++] = j + 2;
      indices[i++] = j + 3;
      indices[i++] = j + 2;
      indices[i++] = j + 0;
      j += 4;
    }
  }
  /* vertices and indices objects */
  glGenVertexArrays(1, &vertex_array);
  glGenBuffers(1, &vertex_buffer);
  glGenBuffers(1, &index_buffer);
  glBindVertexArray(vertex_array);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices, GL_STATIC_DRAW);
  /* attributes */
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof (Vertex), (void *)offsetof (Vertex, position));
}

void
renderer_update(void) {
  glClearColor(0.8f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
