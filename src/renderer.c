#include <errno.h>
#include <stdarg.h>
#include <glad/glad.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "include/renderer.h"
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

#define ATLAS_WIDTH 1024
#define ATLAS_HEIGHT 1024

typedef u32 ShaderID, Object, Texture, Framebuffer, Renderbuffer;
typedef i32 Uniform;

typedef struct { f32 r, g, b, a; } Blend;

typedef struct {
  V2f position;
  V2f texcoord;
  Blend blend;
} Vertex;

typedef struct {
  ShaderID id;
  Uniform camera;
} Shader;

typedef struct {
  Vertex v[4];
} Quad;

typedef struct {
  u32 start_x;
  u32 end_x;
  f32 width_unit;
} Glyph;

static Shader default_shader;

static Object vertex_array;
static Object vertex_buffer;
static Object index_buffer;

static usize render_requests_amount[LAYERS_CAP];
static Quad  render_requests[LAYERS_CAP][QUADS_CAP];

static usize quads_amount;

static Vertex vertices[VERTICES_CAP];

#define FONT_GLYPHS_AMOUNT 95
static Texture atlas;
static Glyph font[FONT_GLYPHS_AMOUNT];

//static Framebuffer framebuffers[RENDER_TARGET_AMOUNT];
//static Renderbuffer renderbuffers[RENDER_TARGET_AMOUNT];

#if DEVMODE
    _Static_assert(RENDER_TARGET_AMOUNT == 3, "not all render targets are handled here");
#endif
static Framebuffer framebuffer;
static Renderbuffer renderbuffer;
static const u32 rendertarget_width[RENDER_TARGET_AMOUNT]                  = { UI_W_PX, GAME_W_PX, SCREEN_W_PX };
static const u32 rendertarget_height[RENDER_TARGET_AMOUNT]                 = { UI_H_PX, GAME_H_PX, SCREEN_H_PX };
static const u32 rendertarget_x[RENDER_TARGET_AMOUNT]                      = { UI_X_PX, GAME_X_PX, SCREEN_X_PX };
static const u32 rendertarget_y[RENDER_TARGET_AMOUNT]                      = { UI_Y_PX, GAME_Y_PX, SCREEN_Y_PX };
static const CameraProjFn rendertarget_projection_fn[RENDER_TARGET_AMOUNT] = { camera_ui_matrix, camera_game_matrix, camera_screen_matrix };


#if DEVMODE
static void
gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *user_param) {
  (void)length; (void)user_param;
  char *source_str, *type_str, *severity_str;
  switch (source) {
    case GL_DEBUG_SOURCE_API: source_str = "API"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM: source_str = "Window System"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY: source_str = "Third Party"; break;
    case GL_DEBUG_SOURCE_APPLICATION: source_str = "Application"; break;
    case GL_DEBUG_SOURCE_OTHER: source_str = "Other"; break;
    default: ERROR("%s:%u: Unrechable", __FILE__, __LINE__); break;
  }
  switch (type) {
    case GL_DEBUG_TYPE_ERROR: type_str = "Error"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: type_str = "Deprecated Behavior"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: type_str = "Undefined Behavior"; break;
    case GL_DEBUG_TYPE_PORTABILITY: type_str = "Portability"; break;
    case GL_DEBUG_TYPE_PERFORMANCE: type_str = "Performance"; break;
    case GL_DEBUG_TYPE_MARKER: type_str = "Marker"; break;
    case GL_DEBUG_TYPE_PUSH_GROUP: type_str = "Push Group"; break;
    case GL_DEBUG_TYPE_POP_GROUP: type_str = "Pop Group"; break;
    case GL_DEBUG_TYPE_OTHER: type_str = "Other"; break;
    default: ERROR("%s:%u: Unrechable", __FILE__, __LINE__); break;
  }
  switch (severity) {
    case GL_DEBUG_SEVERITY_LOW: severity_str = "Low"; break;
    case GL_DEBUG_SEVERITY_MEDIUM: severity_str = "Medium"; break;
    case GL_DEBUG_SEVERITY_HIGH: severity_str = "High"; break;
    default: ERROR("%s:%u: Unrechable", __FILE__, __LINE__); break;
  }
  ERROR("OpenGL Debug Callback: %s: %s: %s: id %u: %s", source_str, type_str, severity_str, id, message);
}
#endif

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

void
renderer_create(void) {
#if DEVMODE
  /* debug */
  i32 context_flags = 0;
  glGetIntegerv(GL_CONTEXT_FLAGS, &context_flags);
  if (context_flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
    INFO("OpenGL debug context created");
    glEnable(GL_DEBUG_OUTPUT);
    //glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(gl_debug_callback, 0);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, 0, GL_FALSE);
    glDebugMessageControl(GL_DEBUG_SOURCE_SHADER_COMPILER, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_FALSE);
  } else {
    WARN("OpenGL debug context not created");
  }
#endif
  /* load atlas */
  u16 atlas_w, atlas_h;
  FILE *atlas_f = fopen("res/images/atlas.tga", "rb");
#if DEVMODE
  if (!atlas_f) ERROR("Couldn't open atlas: %s", strerror(errno));
#endif
  fseek(atlas_f, 12, SEEK_SET);
  fread(&atlas_w, sizeof (u16), 1, atlas_f);
  fread(&atlas_h, sizeof (u16), 1, atlas_f);
  fseek(atlas_f, 2, SEEK_CUR);
  u32 *atlas_buff = malloc(4 * atlas_w * atlas_h);
  fread(atlas_buff, 4, atlas_w * atlas_h, atlas_f);
  /* create font */
  u32 pixel_x = 0;
  for (u32 i = 0; i < FONT_GLYPHS_AMOUNT; i++) {
    u8 pixel_alpha;
    for (; pixel_x < ATLAS_WIDTH; pixel_x++) {
      pixel_alpha = atlas_buff[pixel_x] & 0xFF;
      if (pixel_alpha) break;
    }
    font[i].start_x = pixel_x;
    for (; pixel_x < ATLAS_WIDTH; pixel_x++) {
      pixel_alpha = atlas_buff[pixel_x] & 0xFF;
      if (!pixel_alpha) break;
    }
    font[i].end_x = pixel_x;
    font[i].width_unit = (font[i].end_x - font[i].start_x) * PX_TO_UNIT;
    for (u32 y = 0; y < 8; y++) {
      for (u32 x = font[i].start_x; x < font[i].end_x; x++) {
        u32 pixel = y * ATLAS_WIDTH + x;
        if (atlas_buff[pixel] == 0xFFFF00FF) atlas_buff[pixel] = 0;
      }
    }
  }
  /* atlas texture */
  glGenTextures(1, &atlas);
  glBindTexture(GL_TEXTURE_2D, atlas);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, atlas_w, atlas_h, 0, GL_BGRA, GL_UNSIGNED_BYTE, atlas_buff);
  free(atlas_buff);
  /* render targets */
  glEnable(GL_SCISSOR_TEST);
  glGenFramebuffers(1, &framebuffer);
  glGenRenderbuffers(1, &renderbuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
  glViewport(0, 0, SCREEN_W_PX, SCREEN_H_PX);
  glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, SCREEN_W_PX, SCREEN_H_PX);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffer);
  /* shaders */
  default_shader = renderer_shader_load("default");
  glUseProgram(default_shader.id);
  /* indices setup */
  u32 indices[INDICES_CAP];
  {
    u32 i = 0, j = 0;
    while (i < INDICES_CAP) {
      indices[i++] = j + 0;
      indices[i++] = j + 1;
      indices[i++] = j + 2;
      indices[i++] = j + 2;
      indices[i++] = j + 3;
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
  glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), 0, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices, GL_STATIC_DRAW);
  /* attributes */
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof (Vertex), (void *)offsetof (Vertex, position));
  glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof (Vertex), (void *)offsetof (Vertex, texcoord));
  glVertexAttribPointer(2, 4, GL_FLOAT, false, sizeof (Vertex), (void *)offsetof (Vertex, blend));
  /* blending */
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

static void
renderer_request_quad(V2f position[4], Blend blend, V2i texcoord_start, V2i texcoord_end, Layer layer, const char *file, u32 line) {
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

  quad->v[0].blend = blend;
  quad->v[1].blend = blend;
  quad->v[2].blend = blend;
  quad->v[3].blend = blend;

  quad->v[0].position = position[0];
  quad->v[1].position = position[1];
  quad->v[2].position = position[2];
  quad->v[3].position = position[3];

  quad->v[0].texcoord = V2F(texcoord_start.x, texcoord_end.y  );
  quad->v[1].texcoord = V2F(texcoord_end.x,   texcoord_end.y  );
  quad->v[2].texcoord = V2F(texcoord_end.x,   texcoord_start.y);
  quad->v[3].texcoord = V2F(texcoord_start.x, texcoord_start.y);
}

static void
renderer_request_quad_center(V2f center, V2f size, Blend blend, V2i texcoord_start, V2i texcoord_end, Layer layer, const char *file, u32 line) {
  V2f position[4] = {
    V2F(center.x - size.x * 0.5f, center.y - size.y * 0.5f),
    V2F(center.x + size.x * 0.5f, center.y - size.y * 0.5f),
    V2F(center.x + size.x * 0.5f, center.y + size.y * 0.5f),
    V2F(center.x - size.x * 0.5f, center.y + size.y * 0.5f)
  };
  renderer_request_quad(position, blend, texcoord_start, texcoord_end, layer, file, line);
}

static void
renderer_request_quad_top_left(V2f top_left, V2f size, Blend blend, V2i texcoord_start, V2i texcoord_end, Layer layer, const char *file, u32 line) {
  V2f position[4] = {
    V2F(top_left.x         , top_left.y - size.y),
    V2F(top_left.x + size.x, top_left.y - size.y),
    V2F(top_left.x + size.x, top_left.y         ),
    V2F(top_left.x         , top_left.y         )
  };
  renderer_request_quad(position, blend, texcoord_start, texcoord_end, layer, file, line);
}

void
__renderer_rect(V2f position, V2f size, bool center, f32 r, f32 g, f32 b, f32 a, Layer layer, const char *file, u32 line) {
  if (center) {
    renderer_request_quad_center(position, size, (Blend){r,g,b,a}, V2I(ATLAS_WIDTH-1, ATLAS_HEIGHT-1), V2I(ATLAS_WIDTH, ATLAS_HEIGHT), layer, file, line);
  } else {
    renderer_request_quad_top_left(position, size, (Blend){r,g,b,a}, V2I(ATLAS_WIDTH-1, ATLAS_HEIGHT-1), V2I(ATLAS_WIDTH, ATLAS_HEIGHT), layer, file, line);
  }
}

void
__renderer_sprite(V2f position, V2i sprite_start, V2i sprite_end, V2f scale, bool center, f32 r, f32 g, f32 b, f32 a, Layer layer, const char *file, u32 line) {
  Blend blend = { r,g,b,a };
  if (center) {
    renderer_request_quad_center(position, scale, blend, sprite_start, sprite_end, layer, file, line);
  } else {
    renderer_request_quad_top_left(position, scale, blend, sprite_start, sprite_end, layer, file, line);
  }
}

static V2f
renderer_text_dimensions_non_variadic(f32 scale, const char *str) {
  V2f dim = { 0, 1 };
  f32 cur_x = 0;
  for (u32 i = 0; i < 1024; i++) {
    u32 glyph_index = 94;
    if (str[i] == '\0') {
      break;
    } else if (str[i] == '\n') {
      if (cur_x > dim.x) dim.x = cur_x;
      dim.x = 0;
      dim.y += scale;
      continue;
    } else if (str[i] == ' ') {
      dim.x += 5*PX_TO_UNIT * scale;
      continue;
    } else if (str[i] >= '!' && str[i] <= '~') {
      glyph_index = str[i] - '!';
    }
    dim.x += (font[glyph_index].width_unit + PX_TO_UNIT) * scale;
  }
  if (cur_x > dim.x) dim.x = cur_x;
  return dim;
}

V2f
renderer_text_dimensions(f32 scale, const char *fmt, ...) {
  va_list args;
  char str[1024];
  va_start(args, fmt);
  vsnprintf(str, 1024, fmt, args);
  va_end(args);
  return renderer_text_dimensions_non_variadic(scale, str);
}

void
__renderer_text(V2f position, f32 scale, bool center_x, bool center_y, f32 r, f32 g, f32 b, f32 a, Layer layer, const char *file, u32 line, const char *fmt, ...) {
  va_list args;
  char str[1024];
  va_start(args, fmt);
  vsnprintf(str, 1024, fmt, args);
  va_end(args);
  if (center_x || center_y) {
    V2f size = renderer_text_dimensions_non_variadic(scale, str);
    position.x -= size.x * 0.5f * center_x;
    position.y += size.y * 0.5f * center_y;
  }
  V2f glyph_pos = position;
  for (u32 i = 0; i < 1024; i++) {
    u32 glyph_index = 94;
    if (str[i] == '\0') {
      break;
    } else if (str[i] == '\n') {
      glyph_pos.x = position.x;
      glyph_pos.y -= scale;
      continue;
    } else if (str[i] == ' ') {
      glyph_pos.x += 5*PX_TO_UNIT * scale;
      continue;
    } else if (str[i] >= '!' && str[i] <= '~') {
      glyph_index = str[i] - '!';
    }
    renderer_request_quad_top_left(glyph_pos, V2F(font[glyph_index].width_unit * scale, scale), (Blend){r,g,b,a}, V2I(font[glyph_index].start_x, 0), V2I(font[glyph_index].end_x, 8), layer, file, line);
    glyph_pos.x += (font[glyph_index].width_unit + PX_TO_UNIT) * scale;
  }
}

void
renderer_batch_start(RenderTarget target) {
  quads_amount = 0;
  glViewport(rendertarget_x[target], rendertarget_y[target], rendertarget_width[target], rendertarget_height[target]);
  glScissor(rendertarget_x[target], rendertarget_y[target], rendertarget_width[target], rendertarget_height[target]);
  glUniformMatrix3fv(default_shader.camera, true, 1, rendertarget_projection_fn[target]());
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
  glBufferSubData(GL_ARRAY_BUFFER, 0, quads_amount * sizeof (Quad), vertices);
  glDrawElements(GL_TRIANGLES, quads_amount * 6, GL_UNSIGNED_INT, 0);
}

void
renderer_to_screen(void) {
  glViewport(0, 0, WINDOW_W, WINDOW_H);
  glScissor(0, 0, WINDOW_W, WINDOW_H);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glBlitFramebuffer(
    0, 0, SCREEN_W_PX, SCREEN_H_PX,
    0, 0, WINDOW_W, WINDOW_H,
    GL_COLOR_BUFFER_BIT, GL_NEAREST
  );

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
  glViewport(0, 0, SCREEN_W_PX, SCREEN_H_PX);
  glScissor(0, 0, SCREEN_W_PX, SCREEN_H_PX);
  glClearColor(COLOR_NR(BORDER_COLOR), COLOR_NG(BORDER_COLOR), COLOR_NB(BORDER_COLOR), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
