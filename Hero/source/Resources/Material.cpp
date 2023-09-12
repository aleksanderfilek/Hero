#include "Material.h"
#include "Shader.h"
#include "../ThirdParty/GL/Gl.h"
#include <cstring>

MaterialParameterUnion::MaterialParameterUnion(const MaterialParameterUnion& Other)
{
    memcpy(this, &Other, sizeof(MaterialParameterUnion));
}

Material::Material(class Shader* Shader, const Map<StringId, MaterialParameter>& Parameters, bool DepthTest)
    :shader(Shader), parameters(Parameters), depthTest(DepthTest)
{
}

void Material::Bind()
{
    if(depthTest)
    {
        glEnable(GL_DEPTH_TEST);
    }
    else
    { 
        glDisable(GL_DEPTH_TEST);
    }

    for(auto& property: parameters)
    {
        switch(property.second.Type)
        {
            case MaterialParameterType::INT:
                shader->SetInt(property.first, property.second.Value.Int);
                break;
            case MaterialParameterType::FLOAT:
                shader->SetFloat(property.first, property.second.Value.Float);
                break;
            case MaterialParameterType::FLOAT3:
                shader->SetFloat3(property.first, property.second.Value.Vec3);
                break;
            case MaterialParameterType::FLOAT4:
                shader->SetFloat4(property.first, property.second.Value.Vec4);
                break;
            case MaterialParameterType::MATRIX3X3:
                shader->SetMatrix3f(property.first, property.second.Value.Mat3);
                break;
            case MaterialParameterType::MATRIX4X4:
                shader->SetMatrix4f(property.first, property.second.Value.Mat4);
                break;
            case MaterialParameterType::TEXTURE:
                shader->SetTexture(property.first, property.second.Value.Texture);
                break;
        }
    }
}
