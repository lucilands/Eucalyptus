#pragma once

const char *frag_src = "#version 450 core

out vec4 FragColor;

in vec2 tex_coord;

uniform vec2 size;
uniform vec4 color;
uniform float radius;

void main() {
   FragColor = color;
}"; // Will be replaced by CMake during configure
const char *vert_src = "#version 450 core
layout (location = 0) in vec4 vertex;

uniform mat4 model;
uniform mat4 projection;

out vec2 tex_coord;

void main() {
   gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
   tex_coord = vertex.zw;
}"; // Will be replaced my CMake during configure
