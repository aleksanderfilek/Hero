#pragma once

#include<cstdint>
#include <unordered_map>
#include<string>

namespace Hero
{

class Shader
{   
private:
    std::string name;
    uint32_t glId;
    std::unordered_map<std::string, uint32_t> uniforms;

    bool isBinded = false;
public:
    HERO Shader(const std::string& _name);
    HERO ~Shader();

    HERO void bind();
    HERO int getUniformLocation(const std::string& _name);

};

}