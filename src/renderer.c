#include "include/renderer.h"
#include <errno.h>
#include <glad/glad.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "include/camera.h"
#include "include/core.h"
#include "include/math.h"
#include "include/types.h"

#define QUADS_CAP    10000
#define VERTICES_CAP (QUADS_CAP * 4)
#define INDICES_CAP  (QUADS_CAP * 6)

#define LAYERS_CAP 7
#define LAYER_MIN -(LAYERS_CAP>>1)
#define LAYER_MAX +(LAYERS_CAP>>1)

typedef u32 ShaderID, Object;
typedef i32 Uniform;

typedef struct { f32 r, g, b, a; } Blend;

typedef struct {
  V2f position;
  Blend blend;
} Vertex;

typedef struct {
  ShaderID id;
  Uniform camera;
} Shader;

typedef struct {
  Vertex v[4];
} Quad;

static Shader sh_quad;
static Shader current_shader = { -1, -1 };

static Object vertex_array;
static Object vertex_buffer;
static Object index_buffer;

static usize render_requests_amount[LAYERS_CAP];
static Quad  render_requests[LAYERS_CAP][QUADS_CAP];

static usize quads_amount;

static Vertex vertices[VERTICES_CAP];

static ShaderID
renderer_shader_load_specific(const char *name, GLenum type) {
  const char *type_str = type == GL_VERTEX_SHADER ? "vertex" : "fragment";
  ShaderID shader = glCreateShader(type);
  /* load source */
  usize shader_path_size = strlen(name) + strlen("res/shaders//.glsl") + strlen(type_str) + 1;
  char *shader_path = malloc(shader_path_size);
  snprintf(shader_path, shader_path_size, "res/shaders/%s/%s.glsl", name, type_str);
  FILE *f = fopen(shader_path, "r");
#if DEVMODE
  if (!f) ERROR("Couldn't open '%s': %s", shader_path, strerror(errno));
#endif
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
  glCompileShader(shader);
#if DEVMODE
  i32 status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (!status) {
    i32 log_size;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
    char *log = malloc(log_size);
    glGetShaderInfoLog(shader, log_size, 0, log);
    ERROR("Shader '%s': %s: %.*s", name, type_str, log_size, log);
  }
#endif
  return shader;
}

static Shader
renderer_shader_load(const char *name) {
  Shader shader;
  shader.id = glCreateProgram();
  ShaderID vertex = renderer_shader_load_specific(name, GL_VERTEX_SHADER);
  ShaderID fragment = renderer_shader_load_specific(name, GL_FRAGMENT_SHADER);
  /* link shaders */
  glAttachShader(shader.id, vertex);
  glAttachShader(shader.id, fragment);
  glLinkProgram(shader.id);
  glDeleteShader(vertex);
  glDeleteShader(fragment);
#if DEVMODE
  i32 status;
  glGetProgramiv(shader.id, GL_LINK_STATUS, &status);
  if (!status) {
     i32 log_size;
     glGetProgramiv(shader.id, GL_INFO_LOG_LENGTH, &log_size);
     char *log = malloc(log_size);
     glGetProgramInfoLog(shader.id, log_size, 0, log);
     ERROR("Shader '%s': linking: %.*s", name, log_size, log);
  }
#endif
  /* camera uniform */
  shader.camera = glGetUniformLocation(shader.id, "u_camera");
#if DEVMODE
  if (shader.camera == -1) {
    ERROR("Missing 'u_camera' on shader '%s'", name);
  }
#endif
  return shader;
}

static void
renderer_shader_set(Shader shader) {
  current_shader = shader;
}

void
renderer_create(void) {
  /* shaders */
  sh_quad = renderer_shader_load("quad");
  renderer_shader_set(sh_quad);
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
  glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices, GL_STATIC_DRAW);
  /* attributes */
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof (Vertex), (void *)offsetof (Vertex, position));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof (Vertex), (void *)offsetof (Vertex, blend));
  /* blending */
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void
__renderer_request_quad(V2f position, V2f size, Color color, Layer layer, const char *file, u32 line) {
  quads_amount++;
#if DEVMODE
  if (quads_amount >= QUADS_CAP) {
    ERROR("%s:%u: Quads capacity exceeded", file, line);
  }
  if (layer < LAYER_MIN || layer > LAYER_MAX) {
    ERROR("%s:%u: Layer out of bounds (%d to %d)", file, line, LAYER_MIN, LAYER_MAX);
  }
#endif
  layer += LAYER_MAX;
  Quad *quad = &render_requests[layer][render_requests_amount[layer]++];
  Blend blend = {
    (f32)((color >> 24) & 0xFF) / 255,
    (f32)((color >> 16) & 0xFF) / 255,
    (f32)((color >>  8) & 0xFF) / 255,
    (f32)((color >>  0) & 0xFF) / 255
  };

  quad->v[0].blend = blend;
  quad->v[1].blend = blend;
  quad->v[2].blend = blend;
  quad->v[3].blend = blend;

  quad->v[0].position = V2F(position.x - size.x * 0.5f, position.y - size.y * 0.5f);
  quad->v[1].position = V2F(position.x + size.x * 0.5f, position.y - size.y * 0.5f);
  quad->v[2].position = V2F(position.x + size.x * 0.5f, position.y + size.y * 0.5f);
  quad->v[3].position = V2F(position.x - size.x * 0.5f, position.y + size.y * 0.5f);
}

void
renderer_batch_start(void) {
  quads_amount = 0;
  glUseProgram(current_shader.id);
  glUniformMatrix3fv(current_shader.camera, true, 1, camera_matrix());
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void
renderer_batch_end(void) {
  Vertex *vertex = vertices;
  for (usize layer = 0; layer < LAYERS_CAP; layer++) {
    for (usize quad = 0; quad < render_requests_amount[layer]; quad++) {
      *vertex++ = render_requests[layer][quad].v[0];
      *vertex++ = render_requests[layer][quad].v[1];
      *vertex++ = render_requests[layer][quad].v[2];
      *vertex++ = render_requests[layer][quad].v[3];
    }
    render_requests_amount[layer] = 0;
  }
  glBufferSubData(GL_ARRAY_BUFFER, 0, quads_amount * 4 * sizeof (Vertex), vertices);
  glDrawElements(GL_TRIANGLES, quads_amount * 6, GL_UNSIGNED_INT, 0);
}
