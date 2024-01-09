#pragma once
#include <string>

#include "api.h"



namespace Eucalyptus{
    class Error{
    public:
        virtual std::string ToString(){
            return "ERROR: Eucalyptus_" + m_name + ": " + m_message;
        };
    protected:
        std::string m_message;
        std::string m_name = "BasicError";
    };

    std::ostream& operator<<(std::ostream& os, Error err);


    class GLFWWindowError : public Error{
    public:
        GLFWWindowError(std::string message){
            m_message = message;
            m_name = "GLFWWindowError";
        };
    };
    class GLFWInitError : public Error{
    public:
        GLFWInitError(std::string message){
            m_message = message;
            m_name = "GLFWInitError";
        };
    };
    class GLADInitError : public Error{
    public:
        GLADInitError(std::string message){
            m_message = message;
            m_name = "GLADInitError";
        }
    };
    class EUCInitError : public Error{
    public:
        EUCInitError(std::string message){
            m_message = message;
            m_name = "EucalyptusInitError";
        }
    };
    class ShaderCompileError : public Error {
    public:
        ShaderCompileError(std::string message){
            m_message = message;
            m_name = "ShaderCompileError";
        }
    };
    class ShaderLinkError : public Error {
    public:
        ShaderLinkError(std::string message){
            m_message = message;
            m_name = "ShaderLinkError";
        }
    };
}