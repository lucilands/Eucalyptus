#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoord;

uniform mat4 _view;
uniform mat4 _transform;
uniform mat4 _projection;

out vec3 FragPos;
out vec3 Normal;
out vec3 VColor;
out vec2 TexCoord;


void main()
{
    FragPos = vec3(_transform * vec4(aPos, 1.0));
    Normal = aNormal;
    TexCoord = aTexCoord;
	VColor = aColor;

    gl_Position = _projection * _view * vec4(FragPos, 1.0);
}