#include"Core/Debug.hpp"

#include<iostream>
#include<string>

GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
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
        std::cout<<error<<" | "<<file<<" ("<<line<<")"<<std::endl;
    }
    return errorCode;
}

GLint glShaderCheckError_(GLuint shader, GLenum pname ,const char *file, int line)
{
    GLint errorCode;
    glGetShaderiv(shader, pname, &errorCode);
    if(!errorCode)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);

        GLint shaderType;
        glGetShaderiv(shader, GL_SHADER_TYPE, &shaderType);
        switch(shaderType)
        {
        case GL_VERTEX_SHADER:
            std::cout<<"Error: Vertex Shader - ";
            break;
        case GL_GEOMETRY_SHADER:
            std::cout<<"Error: Geometry Shader - ";
            break;
        case GL_FRAGMENT_SHADER:
            std::cout<<"Error: Fragment Shader - ";
            break;
        }

        switch (pname)
        {
        case  GL_DELETE_STATUS :
            std::cout<<"Delete Status Failed ";
            break;
        case  GL_COMPILE_STATUS :
            std::cout<<"Compile Status Failed ";
            break;
        }

        std::cout<<infoLog<<" | "<<file<<" ("<<line<<")"<<std::endl;
    }

    return errorCode;
}

GLint glProgramCheckError_(GLuint program, GLenum pname ,const char *file, int line)
{
    GLint errorCode;
    glGetProgramiv(program, pname, &errorCode);
    if(!errorCode)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        switch(pname)
        {
            case GL_DELETE_STATUS:
                std::cout<<"Delete Status Failed";
            break;
            case GL_ATTACHED_SHADERS:
                std::cout<<"Attach Status Failed";
            break;
            case GL_LINK_STATUS:
                std::cout<<"Link Status Failed";
            break;
        }
        std::cout<<infoLog<<" | "<<file<<" ("<<line<<")"<<std::endl;
    }

    return errorCode;
}