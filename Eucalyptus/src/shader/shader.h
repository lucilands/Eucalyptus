#pragma once
#include "api.h"
#include <vector>

#include "math/vector.h"
#include "math/transform.h"


#include <string>


namespace Eucalyptus {
    class _EUCAPI Shader {
    public:
        Shader(const char* vertexSRC, const char* fragmentSRC);
        void Compile();
        void Use();

        static Shader LoadFromFile(const char* vertexShaderPath, const char* fragmentShaderPath);
        static void _InitShader();

        void SetUniformInt(const char* uniformName, int value);
        void SetUniformFloat(const char* uniformName, float value);
        
        void SetUniformVector2f(const char* uniformName, Math::Vector2f value);
        void SetUniformVector2i(const char* uniformName, Math::Vector2i value);

        void SetUniformVector3f(const char* uniformName, Math::Vector3f value);
        void SetUniformVector3i(const char* uniformName, Math::Vector3i value);

        void SetUniformVector4f(const char* uniformName, Math::Vector4f value);
        void SetUniformVector4i(const char* uniformName, Math::Vector4i value);

        void SetUniformMat4(const char* uniformName, glm::mat4 value);
        void SetUniformView(const char* uniformName, glm::mat4 value);

        void Delete();

        static Shader *Empty;
        static Shader *unlit_shader;
        static Shader *lit_shader;

        const char* vertexSource;
        const char* fragmentSource;

        static std::string fragPath;
        static std::string vertexPath;


        static Shader Unlit() { return *unlit_shader; };
        static Shader Lit() { return *lit_shader; };
    private:
        unsigned int m_ID;
    };
    class _EUCAPI ShaderList {
    public:
        void push_back(Shader* shader);
        Shader* pop_back();
        void reload_shaders();

        std::vector<Shader*> get_list() { return m_list; }
    private:
        std::vector<Shader*> m_list;
    };

    extern _EUCAPI ShaderList shaders;
}