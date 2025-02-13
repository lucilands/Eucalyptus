#version 450 core

out vec4 FragColor;

in vec2 tex_coord;

uniform vec2 size;
uniform vec4 color;
uniform float radius;

void main() 
{
    if (radius <= 0.01) {
        FragColor = color;
        return;
    }
    float m_radius = radius * length(size) / 3;
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
}