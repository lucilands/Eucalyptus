const char *frag_src = R"(#version 450 core

out vec4 FragColor;

in vec2 tex_coord;

uniform vec2 size;
uniform vec4 color;
uniform float radius;

void main() 
{
    float m_radius = radius * length(size);
    // Calculate pixel position relative to the rectangle's center
    vec2 pixelPos = tex_coord * size;
    vec2 halfSize = size * 0.5;
    vec2 d = abs(pixelPos - halfSize) - (halfSize - vec2(m_radius));

    // Calculate the distance from the rounded corner area
    float dist = length(max(d, 0.0)) - m_radius;

    // Smoothly blend edges using anti-aliasing
    float alpha = smoothstep(0.0, 1.5, -dist);

    // Discard fully transparent fragments
    if (alpha < 0.01) discard;
    
    // Output the rounded rectangle color
    FragColor = vec4(color.rgb, color.a * alpha);
})"; // Will be replaced by CMake during configure
const char *vert_src = R"(#version 450 core
layout (location = 0) in vec4 vertex;

uniform mat4 model;
uniform mat4 projection;

out vec2 tex_coord;

void main() {
   gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
   tex_coord = vertex.zw;
})"; // Will be replaced my CMake during configure
