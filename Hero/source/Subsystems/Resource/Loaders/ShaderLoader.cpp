#include "ShaderLoader.h"
#include "../../../Resources/Shader.h"
#include "../../../Utility/ByteOperations.h"
#include "../../../ThirdParty/GL/Gl.h"
#include "../../../Containers/Array.h"
#include "../../../Containers/Map.h"
#include "../../../GenericTypes/String.h"

ResourceHandle *ShaderLoader::Load(const uint8_t *Data, class ResourceSubsystem *Subsystem)
{
    int index = 0;
    uint32_t program = glCreateProgram();

    uint32_t uniformNumber = 0;
    uint32_t textureUniformNumber = 0;

    uint16_t flags = 0;
    uint32_t size = 0;
    char* content = 0;
    uint32_t typeArr[5] = { GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER,
        GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER };
    uint32_t shaders[5];

    Array<String> uniformVec;
    uniformNumber = ByteOperations::ReadUint32(Data, &index);
    for (int i = 0; i < uniformNumber; i++)
    {
        size = ByteOperations::ReadUint32(Data, &index);

        content = new char[size + 1];
        content[size] = '\0';
        ByteOperations::ReadPtr(Data, &index, (uint8_t*)content, size);

        uniformVec.Add(String(content));

        delete[] content;
    }

    Array<String> textureUniformVec;
    textureUniformNumber = ByteOperations::ReadUint32(Data, &index);
    for (int i = 0; i < textureUniformNumber; i++)
    {
        size = ByteOperations::ReadUint32(Data, &index);

        content = new char[size + 1];
        content[size] = '\0';
        ByteOperations::ReadPtr(Data, &index, (uint8_t*)content, size);

        textureUniformVec.Add(String(content));

        delete[] content;
    }

    flags = ByteOperations::ReadUint16(Data, &index);
    for (int i = 0; i < 5; i++)
    {
        if (!(flags & 1 << i))
        {
            continue;
        }

        size = ByteOperations::ReadUint32(Data, &index);
        content = new char[size + 1];
        content[size] = '\0';
        ByteOperations::ReadPtr(Data, &index, (uint8_t*)content, size);

        shaders[i] = glCreateShader(typeArr[i]);
        glShaderSource(shaders[i], 1, (const char**)&content, nullptr);
        glCompileShader(shaders[i]);
        GlShaderCheckError(shaders[i], GL_COMPILE_STATUS);

        glAttachShader(program, shaders[i]);
        GlProgramCheckError(program, GL_ATTACHED_SHADERS);

        delete[] content;
        content = nullptr;
    }

    glLinkProgram(program);
    int  success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    GlProgramCheckError(program, GL_LINK_STATUS);
    if (success == GL_FALSE)
    {
        exit(-1);
    }

    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
    if (success == GL_FALSE)
    {
        std::cout << "Program is not valid!\n" << std::endl;
        exit(-1);
    }

    for (int i = 0; i < 5; i++)
    {
        if (!(flags & 1 << i))
        {
            continue;
        }

        glDeleteShader(shaders[i]);
        GlShaderCheckError(shaders[i], GL_DELETE_STATUS);
    }

    glUseProgram(program);
    Map<StringId, uint32_t> uniforms;
    for (auto uniform : uniformVec)
    {
        uint32_t loc = glGetUniformLocation(program, *uniform);
        uniforms.Add(StringId(uniform), loc);
    }

    uint32_t textureCounter = 0;
    Map<StringId, uint32_t> textures;
    for (auto uniform : textureUniformVec)
    {
        textures.Add(StringId(uniform), textureCounter);
        textureCounter++;
    }

    return new Shader(program, uniforms, textures);
}

void ShaderLoader::Unload(ResourceHandle *Resource)
{
    //delete Resource;
}