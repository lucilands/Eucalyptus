#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 _transform;
uniform mat4 _view;
uniform mat4 _projection;

out vec2 texcoord;
out vec3 normal;
out vec3 frag_pos;

void main()
{
    gl_Position = _projection * _view * _transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    texcoord = texCoord;
    normal = aNormal;
    frag_pos = vec3(_transform * vec4(aPos, 0.0));
}