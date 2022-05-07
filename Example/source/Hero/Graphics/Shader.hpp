#pragma once

#include"../Core/Math.hpp"
#include"../Core/IResource.hpp"

#include<cstdint>
#include<unordered_map>
#include<string>

namespace Hero
{

class Shader : public IResource
{   
private:
    std::string name;
    uint32_t glId;
    std::unordered_map<std::string, uint32_t> uniforms;

    bool isBinded = false;
public:
    HERO Shader();
    HERO Shader(const std::string& Name, uint32_t GlId, const std::unordered_map<std::string, uint32_t>& Uniforms);

    HERO static IResource* Load(const std::string& path);
    HERO static void Unload(IResource* resource);
    static int GetId(){ return 1; }

    HERO void bind();
    HERO int getUniformLocation(const std::string& _name);
    inline uint32_t getGlId(){ return glId; }
    HERO void setInt(const std::string& _name, int value);
    HERO void setFloat(const std::string& _name, float value);
    HERO void setFloat3(const std::string& _name, const Float3& value);
    HERO void setMatrix4f(const std::string& _name, const Matrix4x4& value);
};

}