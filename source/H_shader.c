#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"H_headers.h"
#include"H_debug.h"

typedef struct 
{
    const char* vertexShader;
    const char* fragmentShader;

    uint32_t glID;
} HeroShader;

HeroShader* heroShaderLoad(const char* vertexShader, const char* fragmentShader)
{
    uint32_t program = glCreateProgram();
    uint32_t vertex = 0, fragment = 0;

    char* buffer = NULL;
    size_t length = 0;

    FILE* file = NULL;

    if(vertexShader)
    {
        file = fopen(vertexShader, "r");

        if(file == NULL)
        {
            printf("Could not open vertex shader file: %s\n", vertexShader);
            return NULL;
        }

        fseek (file, 0, SEEK_END);
        length = ftell(file) + 1;
        fseek (file, 0, SEEK_SET);
        buffer = (char*)malloc(length);
        memset(buffer,0,length);
        fread(buffer, 1, length, file);
        buffer[length] = '\0';

        fclose(file);

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, (const char**)&buffer, NULL);
        glCompileShader(vertex);        
        DEBUG_CODE( glShaderCheckError(vertex, GL_COMPILE_STATUS); )

        glAttachShader(program, vertex);
        DEBUG_CODE( glProgramCheckError(program, GL_ATTACHED_SHADERS); )

        free(buffer);
    }

    if(fragmentShader)
    {
        file = fopen(fragmentShader, "r");

        if(file == NULL)
        {
            printf("Could not open fragment shader file: %s\n", fragmentShader);
            return NULL;
        }

        fseek (file, 0, SEEK_END);
        length = ftell(file) + 1;
        fseek (file, 0, SEEK_SET);
        buffer = (char*)malloc(length);
        memset(buffer,0,length);
        fread(buffer, 1, length, file);
        buffer[length] = '\0';
        fclose(file);

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, (const char**)&buffer, NULL);
        glCompileShader(fragment);
        DEBUG_CODE( glShaderCheckError(fragment, GL_COMPILE_STATUS); )

        glAttachShader(program, fragment);
        DEBUG_CODE( glProgramCheckError(program, GL_ATTACHED_SHADERS); )

        free(buffer);
    }

    glLinkProgram(program);
    int  success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    DEBUG_CODE( glProgramCheckError(program, GL_LINK_STATUS); )
    if(success == GL_FALSE)
    {
        return NULL;
    }

    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
    if(success == GL_FALSE)
    {
        printf("Program is not valid!\n");
        return NULL;
    }

    glDeleteShader(vertex);
    DEBUG_CODE( glShaderCheckError(vertex, GL_DELETE_STATUS); )
    glDeleteShader(fragment);
    DEBUG_CODE( glShaderCheckError(fragment, GL_DELETE_STATUS); )

    HeroShader* shader = (HeroShader*)malloc(sizeof(HeroShader));
    *shader = (HeroShader){ vertexShader, fragmentShader, program };

    return shader;
}

void heroShaderUnload(HeroShader* shader)
{
    glDeleteProgram(shader->glID);
    free(shader);
}

void heroShaderBind(const HeroShader* shader)
{
    glUseProgram(shader->glID);
    glCheckError();
}

uint32_t heroShaderGetUniformLocation(const HeroShader* shader, const char* name)
{
    return glGetUniformLocation(shader->glID, name);
}