#pragma once

#include"Math.hpp"

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
    inline uint32_t getGlId(){ return glId; }
    HERO void setInt(const std::string& _name, int value);
    HERO void setFloat(const std::string& _name, float value);
    HERO void setFloat3(const std::string& _name, const Float3& value);
    HERO void setMatrix4f(const std::string& _name, const Matrix4x4& value);
};

}