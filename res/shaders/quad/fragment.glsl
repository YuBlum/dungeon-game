#version 330

out vec4 f_blend;

in vec4 v_blend;

void
main() {
  f_blend = v_blend;
}
