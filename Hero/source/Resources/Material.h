#pragma once

#include "../Definitions.h"
#include "ResourceHandle.h"
#include "../Math/Float3.h"
#include "../Math/Float4.h"
#include "../Math/Matrix3x3.h"
#include "../Math/Matrix4x4.h"
#include "../Containers/Map.h"

enum class MaterialParameterType
{
    INT =           0,
    FLOAT =         1,
    FLOAT3 =        2,
    FLOAT4 =        3,
    MATRIX3X3 =     4,
    MATRIX4X4 =     5,
    TEXTURE =       6
};

union HERO_API MaterialParameterUnion
{
    int Int;
    float Float;
    Float3 Vec3;
    Float4 Vec4;
    Matrix3x3 Mat3;
    Matrix4x4 Mat4;
    class Texture* Texture;
    
    MaterialParameterUnion():Int(0){}
    MaterialParameterUnion(int Value):Int(Value){}
    MaterialParameterUnion(float Value):Float(Value){}
    MaterialParameterUnion(Float3 Value):Vec3(Value){}
    MaterialParameterUnion(Float4 Value):Vec4(Value){}
    MaterialParameterUnion(Matrix3x3 Value):Mat3(Value){}
    MaterialParameterUnion(Matrix4x4 Value):Mat4(Value){}
    MaterialParameterUnion(class Texture* Value):Texture(Value){}
    MaterialParameterUnion(const MaterialParameterUnion& Other);
};

struct MaterialParameter
{
    MaterialParameterType Type;
    MaterialParameterUnion Value;

    MaterialParameter(){}
    MaterialParameter(const MaterialParameter& Other)
        :Type(Other.Type),Value(Other.Value){}
};

class HERO_API Material : public ResourceHandle
{
private:
    class Shader* shader;
    Map<StringId, MaterialParameter> parameters;
    bool depthTest = false;

public:
    Material(class Shader* Shader, const Map<StringId, MaterialParameter>& Parameters, bool DepthTest);

    class Shader* GetShader() const { return shader; }

    void Bind();
};
