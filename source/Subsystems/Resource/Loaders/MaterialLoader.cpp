#include "MaterialLoader.h"
#include "../../../Resources/Material.h"
#include "../../../Resources/Shader.h"
#include "../../../Resources/Texture.h"
#include "../ResourceSubsystem.h"
#include "../../../Utility/ByteOperations.h"
#include "../../../Containers/Map.h"

ResourceHandle* MaterialLoader::Load(const uint8_t* Data, class ResourceSubsystem* Subsystem)
{
    int index = 0;

    uint32_t shaderId = ByteOperations::ReadUint32(Data, &index);
    Shader* shader = (Shader*)Subsystem->Get(StringId(shaderId));

    bool depthTest = ByteOperations::ReadUint8(Data, &index);

    Map<StringId, MaterialParameter> parameters;
    uint32_t parametersNumber = ByteOperations::ReadUint32(Data, &index);
    for(int i = 0; i < parametersNumber; i++)
    {
        uint32_t parameterId = ByteOperations::ReadUint32(Data, &index);
        uint32_t parameterType = ByteOperations::ReadUint32(Data, &index);

        MaterialParameter parameter;
        parameter.Type = (MaterialParameterType)parameterType;

        switch(parameter.Type)
        {
            case MaterialParameterType::INT:
                ByteOperations::ReadPtr(Data, &index, (uint8_t*)&parameter.Value.Int, sizeof(int));
                break;
            case MaterialParameterType::FLOAT:
                ByteOperations:: ReadPtr(Data, &index, (uint8_t*)&parameter.Value.Float, sizeof(float));
                break;
            case MaterialParameterType::FLOAT3:
                ByteOperations::ReadPtr(Data, &index, (uint8_t*)&parameter.Value.Vec3, sizeof(Float3));
                break;
            case MaterialParameterType::FLOAT4:
                ByteOperations::ReadPtr(Data, &index, (uint8_t*)&parameter.Value.Vec4, sizeof(Float4));
                break;
            case MaterialParameterType::MATRIX3X3:
                ByteOperations::ReadPtr(Data, &index, (uint8_t*)&parameter.Value.Mat3, sizeof(Matrix3x3));
                break;
            case MaterialParameterType::MATRIX4X4:
                ByteOperations::ReadPtr(Data, &index, (uint8_t*)&parameter.Value.Mat4, sizeof(Matrix4x4));
                break;
            case MaterialParameterType::TEXTURE:
                uint32_t textureId;
                ByteOperations::ReadPtr(Data, &index, (uint8_t*)&textureId, sizeof(uint32_t));
                parameter.Value.Texture = (Texture*)Subsystem->Get(StringId(textureId));
                break;
        }

        parameters.Add(StringId(parameterId), parameter);
    }

    return new Material(shader, parameters, depthTest);
}

void MaterialLoader::Unload(ResourceHandle* Resource)
{
    delete Resource;
}
