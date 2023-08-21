#pragma once

#include "../Definitions.h"
#include "ResourceHandle.h"
#include "../GenericTypes/StringId.h"
#include "../Containers/Map.h"
#include <cstdint>
#include "../Math/Float3.h"
#include "../Math/Float4.h"
#include "../Math/Matrix3x3.h"
#include "../Math/Matrix4x4.h"

class HERO_API Shader : public ResourceHandle
{
private:
    uint32_t glId;
    Map<StringId, uint32_t> uniforms;
    Map<StringId, uint32_t> textures;

public:
    Shader(uint32_t GlId, const Map<StringId, uint32_t>& Uniforms,
        const Map<StringId, uint32_t>& Textures);
    ~Shader();

    void Bind();
    uint32_t GetGlId() const { return glId; }
    int GetUniformLocation (StringId Name);
    void SetInt(StringId Name, int Value);
    void SetFloat(StringId Name, float Value);
    void SetFloat3(StringId Name, const Float3& Value);
    void SetFloat4(StringId Name, const Float4& Value);
    void SetMatrix3f(StringId Name, const Matrix3x3& Value);
    void SetMatrix4f(StringId Name, const Matrix4x4& Value);
    void SetTexture(StringId Name, class Texture* Value);
};