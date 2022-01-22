#include"Shader.hpp"
#include"ThirdParty.hpp"
#include"Debug.hpp"

#include<iostream>
#include<fstream>
#include<vector>

namespace Hero
{

HERO Shader::Shader(const std::string& _name)
{
    uint32_t program = glCreateProgram();
    
    uint32_t uniformNumber = 0;
    std::vector<std::string> uniformVec;
    uint16_t flags = 0;
    uint32_t size = 0;
    char* content = 0;
    uint32_t typeArr[5] = { GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, 
        GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER };
    uint32_t shaders[5];


    std::ifstream file(_name, std::ios::binary);
    if(!file.is_open())
    {
        std::cout<<"File could not be opened! Path: "<<_name<<std::endl;
        return;
    }

    file.read((char*)&uniformNumber, sizeof(uint32_t));
    for(int i = 0; i < uniformNumber; i++)
    {
        file.read((char*)&size, sizeof(uint32_t));
        content = new char[size+1];
        file.read(content, size * sizeof(char));
        content[size]='\0';

        std::string uniform(content);
        uniformVec.push_back(uniform);

        delete content;
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


        delete content;
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
    for(auto uniform: uniformVec)
    {
        uint32_t loc = glGetUniformLocation(program, uniform.c_str());
        std::cout<<"Uniform: "<<loc<<" - "<<uniform.c_str()<<std::endl;
        uniforms.insert({uniform, loc});
    }
    
    name = _name;
    glId = program;
}

HERO Shader::~Shader()
{
    glDeleteProgram(glId);
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

}