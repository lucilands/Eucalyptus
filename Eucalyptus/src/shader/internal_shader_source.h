#pragma once



const char* unlit_vertex = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 2) in vec3 aColor;\n"
        "layout (location = 3) in vec2 aTexCoord;\n"

        "uniform mat4 _transform;\n"
        "uniform mat4 _view;\n"
        "uniform mat4 _projection;\n"

        "out vec3 FragPos;\n"
        "out vec3 VColor;\n"
        "out vec2 TexCoord;\n"

        "void main()\n"
        "{\n"
            "TexCoord = aTexCoord;\n"
	        "VColor = aColor;\n"
    	    "gl_Position = _projection * _view * _transform * vec4(aPos, 1.0);\n"
        "}";

const char* unlit_fragment = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"

        "uniform vec3 _color;\n"
        "uniform sampler2D tex;\n"

        "in vec3 VColor;\n"
        "in vec2 TexCoord;\n"
    
        "void main()\n"
        "{\n"
        "   FragColor = vec4(_color, 1.0) * texture(tex, TexCoord);"
        "}";

const char* lit_vertex = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aNormal;\n"
        "layout (location = 2) in vec3 aColor;\n"
        "layout (location = 3) in vec2 aTexCoord;\n"

        "uniform mat4 _view;\n"
        "uniform mat4 _transform;\n"
        "uniform mat4 _projection;\n"

        "out vec3 FragPos;\n"
        "out vec3 Normal;\n"
        "out vec3 VColor;\n"
        "out vec2 TexCoord;\n"
        "void main()\n"
        "{\n"
        "    FragPos = vec3(_transform * vec4(aPos, 1.0));\n"
        "    Normal = aNormal;\n"
        "    TexCoord = aTexCoord;\n"
        "	 VColor = aColor;\n"
        
        "    gl_Position = _projection * _view * vec4(FragPos, 1.0);\n"
        "}";
const char* lit_fragment = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"

        "in vec3 Normal;  \n"
        "in vec3 FragPos; \n"
        "in vec3 VColor;\n"
        "in vec2 TexCoord;\n"

        "uniform vec3 _emission_color;\n"
        "uniform vec3 _color;\n"
        "uniform sampler2D tex;\n"

        "void main()\n"
        "{\n"
        "    vec4 tex_col = texture(tex, TexCoord);\n"
        "    vec3 col = VColor * vec3(tex_col);\n"

        "    vec3 lightPos = vec3(10.0, 10.0, 10.0);\n"
        "    vec3 viewPos = vec3(0.0, 0.0, -10.0); \n"

        "    // ambient\n"
        "    float ambientStrength = 1.0;\n"
        "    vec3 ambient = ambientStrength * _emission_color;\n"

        "    // diffuse \n"
        "    vec3 norm = normalize(Normal);\n"
        "    vec3 lightDir = normalize(lightPos - FragPos);\n"
        "    float diff = max(dot(norm, lightDir), 0.0);\n"
        "    vec3 diffuse = diff * _emission_color;\n"

        "    // specular\n"
        "    float specularStrength = 1.0;\n"
        "    vec3 viewDir = normalize(viewPos - FragPos);\n"
        "    vec3 reflectDir = reflect(-lightDir, norm);  \n"
        "    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);\n"
        "    vec3 specular = specularStrength * spec * _emission_color;\n"

        "    vec3 result = (ambient + diffuse + specular) * col;\n"
        "    FragColor = vec4(result, 1.0);\n"
        "}";