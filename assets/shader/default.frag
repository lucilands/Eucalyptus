#version 330 core
out vec4 FragColor;

in vec2 texcoord;
in vec3 normal;
in vec3 frag_pos;

uniform sampler2D tex;
uniform vec3 _viewPos;

const vec3 light_pos = vec3(0.0, 2.0, 2.0);
const vec3 light_color = vec3(1.0, 1.0, 1.0);

const float specular_strength = 0.5;
const float ambientStrength = 0.3;

const int specular_exponent = 32;

void main()
{
    vec3 color = texture(tex, texcoord).rgb;

    //Light Calculations
    vec3 ambient = ambientStrength * light_color;

    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light_pos - frag_pos);
    vec3 view_dir = normalize(_viewPos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);
    
    float diff = max(dot(normal, light_dir), 0.0);
    vec3 diffuse = diff * light_color;

    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), specular_exponent);
    vec3 specular = specular_strength * spec * light_color;
    
    vec3 result = (ambient + diffuse + specular) * color;

    FragColor = vec4(result, 1.0);
}