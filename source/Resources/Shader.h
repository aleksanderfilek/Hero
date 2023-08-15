// #pragma once

// #include "../Defaults.h"
// #include "ResourceSubsystem.h"
// #include "../Core/Math.h"
// #include "../Core/StringId.h"
// #include <map>

// class HERO_API Shader : public ResourceHandle
// {
// private:
//     uint32_t mGlId;
//     std::map<StringId, uint32_t> mUniforms;
//     std::map<StringId, uint32_t> mTextures;

//     bool isBinded = false;
// public:
//     Shader();
//     ~Shader();

//     static ResourceHandle* load(const uint8_t* Data, ResourceSubsystem* subsystem);
//     static void unload(ResourceHandle* resource);
//     static int getId() { return SHADER_ID; }

//     void bind();
//     int getUniformLocation(StringId name);
//     inline uint32_t getGlId() { return mGlId; }
//     void setInt(StringId name, int value);
//     void setFloat(StringId name, float value);
//     void setFloat3(StringId name, const Float3& value);
//     void setFloat4(StringId name, const Float4& value);
//     void setMatrix3f(StringId name, const Matrix3x3& value);
//     void setMatrix4f(StringId name, const Matrix4x4& value);
//     void setTexture(StringId name, class Texture* value);
// };