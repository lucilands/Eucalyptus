#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos; 
in vec3 VColor;
in vec2 TexCoord;
  
uniform vec3 _emission_color;
uniform vec3 _color;
uniform sampler2D tex;


void main()
{
    vec4 tex_col = texture(tex, TexCoord);
    vec3 col = VColor * vec3(tex_col);

    vec3 lightPos = vec3(10.0, 10.0, 10.0);
    vec3 viewPos = vec3(0.0, 0.0, -10.0); 


    // ambient
    float ambientStrength = 1.0;
    vec3 ambient = ambientStrength * _emission_color;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * _emission_color;
    
    // specular
    float specularStrength = 0.0;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * _emission_color;
        
    vec3 result = (ambient + diffuse + specular) * col;
    FragColor = vec4(result, 1.0);
} 