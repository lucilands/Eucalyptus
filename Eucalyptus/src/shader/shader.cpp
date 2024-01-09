#include "internal.h"

#include "shader.h"
#include "internal_shader_source.h"

#include "error/error.h"
#include "window/window.h"

#include <fstream>
#include <string>
#include <ios>

#include <glad/glad.h>
#include <GLFW/glfw3.h>




namespace Eucalyptus {
    Shader* Shader::Empty = nullptr;
    Shader* Shader::unlit_shader = nullptr;
    Shader* Shader::lit_shader = nullptr;

    std::string Shader::fragPath = "";
    std::string Shader::vertexPath = "";
    ShaderList shaders;

    Shader::Shader(const char* vertexSRC, const char* fragmentSRC) : vertexSource(vertexSRC), fragmentSource(fragmentSRC) {
        shaders.push_back(this);
        if (!_GLINIT){
            _EUC_LOG_ERR(EUCInitError("Cannot create shader because: Eucalyptus window is not initialized yet"));
            _EUC_LOG_INFO("Aborting shader creation");
            return;
        }

        Compile();
    }
    void Shader::Compile(){
        _EUC_LOG_INFO("Creating fragment and vertex shaders");
        unsigned int vShader;
        unsigned int fShader;
        vShader = glCreateShader(GL_VERTEX_SHADER);
        if (!vShader){_EUC_LOG_ERR("Failed to create vertex shader"); _EUC_LOG_INFO("Aborting shader creation"); return;}
        fShader = glCreateShader(GL_FRAGMENT_SHADER);
        if (!fShader){_EUC_LOG_ERR("Failed to create fragment shader"); _EUC_LOG_INFO("Aborting shader creation"); return;}


        int vCompileStatus;
        char vCompileErrMSG[512];
        int fCompileStatus;
        char fCompileErrMSG[512];
        int shaderLinkStatus;
        char shaderLinkErrMSG[512];
        _EUC_LOG_INFO("Compiling fragment and vertex shaders");

        glShaderSource(vShader, 1, &vertexSource, NULL);
        glShaderSource(fShader, 1, &fragmentSource, NULL);
        glCompileShader(vShader);
        glCompileShader(fShader);

        glGetShaderiv(vShader, GL_COMPILE_STATUS, &vCompileStatus);
        glGetShaderiv(fShader, GL_COMPILE_STATUS, &fCompileStatus);

        if (!vCompileStatus) {
            glGetShaderInfoLog(vShader, 512, NULL, vCompileErrMSG);
            _EUC_LOG_ERR(ShaderCompileError("Could not compile vertex shader because:\n" + (std::string)vCompileErrMSG));
            _EUC_LOG_INFO("Aborting shader creation");

            glDeleteShader(vShader);
            glDeleteShader(fShader);
            return;
        }
        _EUC_LOG_INFO("Vertex shader compiled successfully");

        if (!fCompileStatus) {
            glGetShaderInfoLog(fShader, 512, NULL, fCompileErrMSG);
            _EUC_LOG_ERR(ShaderCompileError("Could not compile fragment shader because:\n" + (std::string)fCompileErrMSG));
            _EUC_LOG_INFO("Aborting shader creation");

            glDeleteShader(vShader);
            glDeleteShader(fShader);
            return;
        }
        _EUC_LOG_INFO("Fragment shader compiled successfully");

        _EUC_LOG_INFO("Creating shader program");
        m_ID = glCreateProgram();
        glAttachShader(m_ID, vShader);
        glAttachShader(m_ID, fShader);

        _EUC_LOG_INFO("Linking shader program");
        glLinkProgram(m_ID);

        glGetProgramiv(m_ID, GL_LINK_STATUS, &shaderLinkStatus);
        if (!shaderLinkStatus) {
            glGetProgramInfoLog(m_ID, 512, NULL, shaderLinkErrMSG);
            _EUC_LOG_ERR(ShaderLinkError("Could not link shader program because:\n" + (std::string)shaderLinkErrMSG));
            _EUC_LOG_INFO("Aborting shader creation");

            glDeleteShader(vShader);
            glDeleteShader(fShader);
            return;
        }

        _EUC_LOG_INFO("Cleaning up after shader compilations");

        glDeleteShader(vShader);
        glDeleteShader(fShader);

        _EUC_LOG_INFO("Shader compiled and created");
    }

    void Shader::Use() {
        glUseProgram(m_ID);
    }
    
    Shader Shader::LoadFromFile(const char* vertexShaderPath, const char* fragmentShaderPath) {
        vertexPath = vertexShaderPath;
        fragPath = fragmentShaderPath;
        _EUC_LOG_INFO("Reading shaders from files");

        _EUC_LOG_INFO("Reading vertex shader from file ", "");
        _EUC_LOG_INFO(vertexShaderPath);
        std::ifstream vertexFile(vertexShaderPath);
        if (!vertexFile.is_open()) {
            _EUC_LOG_ERR("Failed to read vertex shader");
            _EUC_LOG_INFO("Aborting reading/parsing");
            return *Empty;
        }

        _EUC_LOG_INFO("Reading fragment shader from file ", "");
        _EUC_LOG_INFO(fragmentShaderPath);
        std::ifstream fragmentFile(fragmentShaderPath);
        if (!fragmentFile.is_open()) {
            _EUC_LOG_ERR("Failed to read fragment shader");
            _EUC_LOG_INFO("Aborting reading/parsing");
            return *Empty;
        }

        std::stringstream vertexSrc;
        std::stringstream fragmentSrc;

        std::string line;
        
        _EUC_LOG_INFO("Reading Vertex shader");
        while (getline(vertexFile, line)) {
            vertexSrc << line << "\n";
        }
        _EUC_LOG_INFO("Read Vertex shader");
        _EUC_LOG_INFO("Reading Fragment shader");
        while (getline(fragmentFile, line)) {
            fragmentSrc << line << "\n";
        }
        _EUC_LOG_INFO("Read Fragment shader");

        _EUC_LOG_INFO("Creating shader object");
        return Shader(vertexSrc.str().c_str(), fragmentSrc.str().c_str());
    }

    void Shader::_InitShader() {
        Empty = new Shader("#version 330 core\nvoid main(){}", "#version 330 core\nvoid main(){}");
        unlit_shader = new Shader(unlit_vertex, unlit_fragment);
        lit_shader = new Shader(lit_vertex, lit_fragment);
    }
    void Shader::SetUniformInt(const char *uniformName, int value) {
        int location = glGetUniformLocation(m_ID, uniformName);
        glUniform1i(location, value);
    }
    void Shader::SetUniformFloat(const char *uniformName, float value) {
        int location = glGetUniformLocation(m_ID, uniformName);
        glUniform1f(location, value);
    }

    void Shader::SetUniformVector2f(const char *uniformName, Math::Vector2f value) {
        int location = glGetUniformLocation(m_ID, uniformName);
        glUniform2f(location, value.x, value.y);
    }
    void Shader::SetUniformVector2i(const char *uniformName, Math::Vector2i value) {
        int location = glGetUniformLocation(m_ID, uniformName);
        glUniform2i(location, value.x, value.y);
    }

    void Shader::SetUniformVector3i(const char *uniformName, Math::Vector3i value) {
        int location = glGetUniformLocation(m_ID, uniformName);
        glUniform3i(location, value.x, value.y, value.z);
    }
    void Shader::SetUniformVector3f(const char *uniformName, Math::Vector3f value) {
        int location = glGetUniformLocation(m_ID, uniformName);
        glUniform3f(location, value.x, value.y, value.z);
    }

    void Shader::SetUniformVector4i(const char *uniformName, Math::Vector4i value) {
        int location = glGetUniformLocation(m_ID, uniformName);
        glUniform4i(location, value.x, value.y, value.z, value.w);
    }
    void Shader::SetUniformMat4(const char *uniformName, glm::mat4 value) {
        int location = glGetUniformLocation(m_ID, uniformName);
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }
    void Shader::SetUniformView(const char *uniformName, glm::mat4 value) {
        int location = glGetUniformLocation(m_ID, uniformName);
        glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
    }
    void Shader::SetUniformVector4f(const char *uniformName, Math::Vector4f value)
    {
        int location = glGetUniformLocation(m_ID, uniformName);
        glUniform4i(location, value.x, value.y, value.z, value.w);
    }

    void Shader::Delete() {
        glDeleteProgram(m_ID);
    }

    // ShaderList
    void ShaderList::push_back(Shader *shader) {
        m_list.push_back(shader);
    }
    Shader* ShaderList::pop_back() {
        Shader* o = m_list.at(m_list.size());
        m_list.pop_back();
        return o;
    }
    void ShaderList::reload_shaders() {
        for (Shader* s : m_list) {
            std::stringstream ss;
            ss << "Recompiling shader: " << s->fragPath << ", " << s->vertexPath;
            _EUC_LOG_INFO(ss.str());
            
            *s = Shader::LoadFromFile(s->vertexPath.c_str(), s->fragPath.c_str());
        }
    }
}