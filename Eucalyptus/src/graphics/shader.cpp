#include <Eucalyptus/graphics/shader.h>

#include <clog.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>

const ClogLevel SHADER_ERROR = CLOG_REGISTER_LEVEL("Shader compilation Error", CLOG_COLOR_RED CLOG_COLOR_BOLD, 6);

namespace Eucalyptus {
    Shader::Shader(const char *vert_src, const char *frag_src) {
        unsigned int vert_id = glCreateShader(GL_VERTEX_SHADER);
        unsigned int frag_id = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(vert_id, 1, &vert_src, nullptr);
        glShaderSource(frag_id, 1, &frag_src, nullptr);

        glCompileShader(vert_id);

        int  success;
        char infoLog[512];
        glGetShaderiv(vert_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vert_id, 512, nullptr, infoLog);
            clog(SHADER_ERROR, "Vertex shader:\n%s", infoLog);
        }

        glCompileShader(frag_id);

        glGetShaderiv(frag_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(frag_id, 512, nullptr, infoLog);
            clog(SHADER_ERROR, "Fragment shader:\n%s", infoLog);
        }

        m_ID = glCreateProgram();

        glAttachShader(m_ID, vert_id);
        glAttachShader(m_ID, frag_id);
        glLinkProgram(m_ID);

        glDeleteProgram(vert_id);
        glDeleteProgram(frag_id);
    }

    Shader Shader::FromFile(const char *vert_path, const char *frag_path) {
        std::ifstream v(vert_path);
        std::string v_str((std::istreambuf_iterator<char>(v)), std::istreambuf_iterator<char>());
        std::ifstream f(frag_path);
        std::string f_str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

        return Shader(v_str.c_str(), f_str.c_str());
    }

    void Shader::Use() {
        glUseProgram(m_ID);
    }

    void Shader::SetMat4(const char *name, const glm::mat4 mat4) {
        glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, &mat4[0][0]);
    }

    void Shader::SetFloat(const char *name, const float val) {
        //clog(CLOG_TRACE, "Shader::SetFloat(\"%s\", %f);", name, val);
        glUniform1f(glGetUniformLocation(m_ID, name), val);
    }

    void Shader::SetVec3(const char *name, const Vector3f val) {
        glUniform3f(glGetUniformLocation(m_ID, name), val.x, val.y, val.z);
    }

    void Shader::SetVec4(const char *name, const Vector4f val) {
        glUniform4f(glGetUniformLocation(m_ID, name), val.x, val.y, val.z, val.w);
    }

    void Shader::SetVec2(const char *name, const Vector2f val) {
        //clog(CLOG_TRACE, "Shader::SetVec2(\"%s\", (Vector2f) {%f, %f});", name, val.x, val.y);
        glUniform2f(glGetUniformLocation(m_ID, name), val.x, val.y);
    }
}