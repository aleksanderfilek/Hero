#include"Shader.hpp"
#include"ThirdParty.hpp"
#include"Debug.hpp"

#include<iostream>
#include<fstream>
#include<vector>

namespace Hero
{

HERO Shader::Shader()
{ 
    id = GetId(); 
}

HERO Shader::Shader(const std::string& Name, uint32_t GlId, 
    const std::unordered_map<std::string, uint32_t>& Uniforms)
    :name(Name), glId(GlId), uniforms(Uniforms)
{

}

HERO IResource* Shader::Load(const std::string& path)
{
    uint32_t program = glCreateProgram();
    
    uint32_t uniformNumber = 0;

    uint16_t flags = 0;
    uint32_t size = 0;
    char* content = 0;
    uint32_t typeArr[5] = { GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, 
        GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER };
    uint32_t shaders[5];

    std::ifstream file(path, std::ios::binary);
    if(!file.is_open())
    {
        std::cout<<"File could not be opened! Path: "<<path<<std::endl;
        return nullptr;
    }

    std::vector<std::string> uniformVec;
    file.read((char*)&uniformNumber, sizeof(uint32_t));
    for(int i = 0; i < uniformNumber; i++)
    {
        file.read((char*)&size, sizeof(uint32_t));
        content = new char[size+1];
        file.read(content, size * sizeof(char));
        content[size]='\0';

        std::string uniform(content);
        uniformVec.push_back(uniform);

        delete[] content;
    }
    file.read((char*)&flags, sizeof(uint16_t));

    for(int i = 0; i < 5; i++)
    {
        if(!(flags & 1<<i))
        {
            continue;
        }

        file.read((char*)&size, sizeof(uint32_t));
        content = new char[size+1];
        content[size]='\0';
        file.read(content, size * sizeof(char));

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

    file.close();

    glUseProgram(program);
    std::unordered_map<std::string, uint32_t> uniforms;
    for(auto uniform: uniformVec)
    {
        uint32_t loc = glGetUniformLocation(program, uniform.c_str());
        uniforms.insert({uniform, loc});
    }
    
    Shader* shader = new Shader(path, program, uniforms);
    return shader;
}

HERO void Shader::Unload(IResource* resource)
{
    glDeleteProgram(((Shader*)resource)->glId);
}

HERO void Shader::bind()
{
    glUseProgram(glId);
    glCheckError();
    isBinded = true;
}

HERO int Shader::getUniformLocation(const std::string& _name)
{
    return (uniforms.find(_name) == uniforms.end())? -1 : uniforms[_name];
}

HERO void Shader::setInt(const std::string& _name, int value)
{
    glUniform1i(getUniformLocation(_name), value); 
}

HERO void Shader::setFloat(const std::string& _name, float value)
{
    glUniform1f(getUniformLocation(_name), value); 
}

HERO void Shader::setFloat3(const std::string& _name, const Float3& value)
{
    glUniform3fv(getUniformLocation(_name), 1, &value.x); 
}

HERO void Shader::setMatrix4f(const std::string& _name, const Matrix4x4& value)
{
    int loc = getUniformLocation(_name);
    #ifdef HERO_DEBUG
    if(loc == -1)
    {
        std::cout<<"Location of "<<_name<<" equales "<<loc<<std::endl;
        return;
    }
    #endif
    glUniformMatrix4fv(getUniformLocation(_name), 1, GL_FALSE, &value.col[0].x); 
}

}