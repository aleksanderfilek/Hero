#include<stdlib.h>
#include<stdio.h>

#include"H_headers.h"

GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        char* error = NULL;
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
        printf("%s | %s (%d)\n", error, file, line);
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
            printf("Error: Vertex Shader - ");
            break;
        case GL_GEOMETRY_SHADER:
            printf("Error: Geometry Shader - ");
            break;
        case GL_FRAGMENT_SHADER:
            printf("Error: Fragment Shader - ");
            break;
        }

        switch (pname)
        {
        case  GL_DELETE_STATUS :
            printf("Delete Status Failed ");
            break;
        case  GL_COMPILE_STATUS :
            printf("Compile Status Failed ");
            break;
        }

        printf("%s | %s (%d)\n", infoLog, file, line);
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
                printf("Delete Status Failed");
            break;
            case GL_ATTACHED_SHADERS:
                printf("Attach Status Failed");
            break;
            case GL_LINK_STATUS:
                printf("Link Status Failed");
            break;
        }
        printf("%s | %s (%d)\n", infoLog, file, line);
    }

    return errorCode;
}