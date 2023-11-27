#include "GlDebug.h"

#include"Gl.h"

#include<iostream>
#include<string>

uint32_t GlDebbug::_InternalGlCheckError(const char* File, int Line)
{
    uint32_t errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
        case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << File << " (" << Line << ")" << std::endl;
    }
    return errorCode;
}

int GlDebbug::_InternalGlShaderCheckError(uint32_t Shader, uint32_t Pname, const char* File, int Line)
{
    int errorCode;
    glGetShaderiv(Shader, Pname, &errorCode);
    if (!errorCode)
    {
        char infoLog[512];
        glGetShaderInfoLog(Shader, 512, NULL, infoLog);

        int shaderType;
        glGetShaderiv(Shader, GL_SHADER_TYPE, &shaderType);
        switch (shaderType)
        {
        case GL_VERTEX_SHADER:
            std::cout << "Error: Vertex Shader - ";
            break;
        case GL_GEOMETRY_SHADER:
            std::cout << "Error: Geometry Shader - ";
            break;
        case GL_FRAGMENT_SHADER:
            std::cout << "Error: Fragment Shader - ";
            break;
        }

        switch (Pname)
        {
        case  GL_DELETE_STATUS:
            std::cout << "Delete Status Failed ";
            break;
        case  GL_COMPILE_STATUS:
            std::cout << "Compile Status Failed ";
            break;
        }

        std::cout << infoLog << " | " << File << " (" << Line << ")" << std::endl;
    }

    return errorCode;
}

int GlDebbug::_InternalGlProgramCheckError(uint32_t Program, uint32_t Pname, const char* File, int Line)
{
    int errorCode;
    glGetProgramiv(Program, Pname, &errorCode);
    if (!errorCode)
    {
        char infoLog[512];
        glGetProgramInfoLog(Program, 512, NULL, infoLog);
        switch (Pname)
        {
        case GL_DELETE_STATUS:
            std::cout << "Delete Status Failed";
            break;
        case GL_ATTACHED_SHADERS:
            std::cout << "Attach Status Failed";
            break;
        case GL_LINK_STATUS:
            std::cout << "Link Status Failed";
            break;
        }
        std::cout << infoLog << " | " << File << " (" << Line << ")" << std::endl;
    }

    return errorCode;
}