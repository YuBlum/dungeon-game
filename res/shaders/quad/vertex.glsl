#version 330

layout (location = 0) in vec2 a_position;

uniform mat3 u_camera;

void
main() {
  gl_Position = vec4(u_camera * vec3(a_position, 0), 1);
}
