#pragma once

#include"../Core/Math.hpp"
#include"../Systems/Resources.hpp"
#include"../Core/Sid.hpp"

#include<cstdint>
#include<unordered_map>
#include<string>

namespace Hero
{

class Shader : public ResourceHandle
{   
private:
    uint32_t glId;
    std::unordered_map<Sid, uint32_t, SidHashFunction> uniforms;

    bool isBinded = false;
public:
    HERO Shader();
    HERO Shader(uint32_t GlId, const std::unordered_map<Sid, uint32_t, SidHashFunction>& Uniforms);
    HERO ~Shader();

    HERO static ResourceHandle* Load(uint8_t* Data);
    HERO static void Unload(ResourceHandle* resource);
    static int GetId(){ return 1; }

    HERO void bind();
    HERO int getUniformLocation(const Sid& name);
    inline uint32_t getGlId(){ return glId; }
    HERO void setInt(const Sid& name, int value);
    HERO void setFloat(const Sid& name, float value);
    HERO void setFloat3(const Sid& name, const Float3& value);
    HERO void setMatrix4f(const Sid& name, const Matrix4x4& value);
};

}