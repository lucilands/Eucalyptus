#version 450 core
layout (location = 0) in vec4 vertex;

uniform mat4 model;
uniform mat4 projection;

out vec2 tex_coord;

void main() {
   gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
   tex_coord = vertex.zw;
}