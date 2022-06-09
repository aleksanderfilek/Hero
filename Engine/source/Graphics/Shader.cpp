#include"Shader.hpp"
#include"../ThirdParty/GL/Gl.hpp"
#include"../Core/Debug.hpp"
#include"../Utility/ByteOperations.hpp"

#include<iostream>
#include<vector>

namespace Hero
{

HERO Shader::Shader()
{ 
    id = GetId(); 
}

HERO Shader::Shader(uint32_t GlId, 
    const std::unordered_map<std::string, uint32_t>& Uniforms)
    :glId(GlId), uniforms(Uniforms)
{}

HERO ResourceHandle* Shader::Load(uint8_t* Data)
{
    int index = 0;
    uint32_t program = glCreateProgram();
    
    uint32_t uniformNumber = 0;

    uint16_t flags = 0;
    uint32_t size = 0;
    char* content = 0;
    uint32_t typeArr[5] = { GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, 
        GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER };
    uint32_t shaders[5];

    std::vector<std::string> uniformVec;
    uniformNumber = ReadUint32(Data, &index);
    for(int i = 0; i < uniformNumber; i++)
    {
        size = ReadUint32(Data, &index);
        content = new char[size+1];
        content[size]='\0';
        ReadPtr(Data, &index, content, size);

        std::string uniform(content);
        uniformVec.push_back(uniform);

        delete[] content;
    }
    flags = ReadUint16(Data, &index);

    for(int i = 0; i < 5; i++)
    {
        if(!(flags & 1<<i))
        {
            continue;
        }

        size = ReadUint32(Data, &index);
        content = new char[size+1];
        content[size]='\0';
        ReadPtr(Data, &index, content, size);

        shaders[i] = glCreateShader(typeArr[i]);
        glShaderSource(shaders[i], 1, (const char**)&content, nullptr);
        glCompileShader(shaders[i]);        
        glShaderCheckError(shaders[i], GL_COMPILE_STATUS);

        glAttachShader(program, shaders[i]);
        glProgramCheckError(program, GL_ATTACHED_SHADERS);


        delete[] content;
        content = nullptr;
    }

    glLinkProgram(program);
    int  success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    glProgramCheckError(program, GL_LINK_STATUS);
    if(success == GL_FALSE)
    {
        exit(-1);
    }

    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
    if(success == GL_FALSE)
    {
        std::cout<<"Program is not valid!\n"<<std::endl;
        exit(-1);
    }

    for(int i = 0; i < 5; i++)
    {
        if(!(flags & 1<<i))
        {
            continue;
        }

        glDeleteShader(shaders[i]);
        glShaderCheckError(shaders[i], GL_DELETE_STATUS);
    }

    glUseProgram(program);
    std::unordered_map<std::string, uint32_t> uniforms;
    for(auto uniform: uniformVec)
    {
        uint32_t loc = glGetUniformLocation(program, uniform.c_str());
        uniforms.insert({SID(uniform), loc});
    }
    
    Shader* shader = new Shader(path, program, uniforms);
    return shader;
}

HERO Shader::~Shader()
{
    glDeleteProgram(glId);
}

HERO void Shader::Unload(ResourceHandle* resource)
{
    delete resource;
}

HERO void Shader::bind()
{
    glUseProgram(glId);
    glCheckError();
    isBinded = true;
}

HERO int Shader::getUniformLocation(const Sid& name)
{
    return (uniforms.find(name) == uniforms.end())? -1 : uniforms[name];
}

HERO void Shader::setInt(const Sid& name, int value)
{
    glUniform1i(getUniformLocation(name), value); 
}

HERO void Shader::setFloat(const Sid& name, float value)
{
    glUniform1f(getUniformLocation(name), value); 
}

HERO void Shader::setFloat3(const Sid& name, const Float3& value)
{
    glUniform3fv(getUniformLocation(name), 1, &value.x); 
}

HERO void Shader::setMatrix4f(const Sid& name, const Matrix4x4& value)
{
    int loc = getUniformLocation(name);
    #ifdef HERO_DEBUG
    if(loc == -1)
    {
        std::cout<<"Location of "<<name<<" equales "<<loc<<std::endl;
        return;
    }
    #endif
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value.col[0].x); 
}

}