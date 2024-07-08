#version 460

out vec4 f_color;

in vec4 v_blend;
in vec2 v_texcoord;

uniform sampler2D tex;

void
main() {
  f_color = texelFetch(tex, ivec2(v_texcoord), 0) * v_blend;
}
