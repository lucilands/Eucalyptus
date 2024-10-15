#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoord;

uniform mat4 _transform;
uniform mat4 _view;
uniform mat4 _projection;

out vec2 texcoord;

void main()
{
    gl_Position = _projection * _view * _transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    texcoord = texCoord;
}