#include "MaterialConverter.h"
#include "../../../Utility/ByteOperations.h"
#include "../../../Math/Float3.h"
#include "../../../Math/Float4.h"
#include "../../../Math/Matrix3x3.h"
#include "../../../Math/Matrix4x4.h"
#include <fstream>
#include <sstream>
#include <string>

void MaterialConverter::GetAcceptableExtensions(Array<const char*>& Extensions)
{
    Extensions.Add("mat");
}

void MaterialConverter::Convert(const char* FilePath)
{
    std::string shaderName;
    int propertiesCount = 0;
    char depthTest = 'f';
    std::string buffer;

    std::ifstream input(FilePath);

    if(!input.is_open())
    {
        return;
    }

    input>>shaderName;
    input>>buffer>>depthTest;
    input>>propertiesCount;

    union MaterialParameterUnion
    {
        int Int;
        float Float;
        Float3 Vec3;
        Float4 Vec4;
        Matrix3x3 Mat3;
        Matrix4x4 Mat4;
        StringId Texture;

        MaterialParameterUnion(){}
        ~MaterialParameterUnion(){}
    };

    Array<MaterialParameterUnion> dataArr;
    Array<uint32_t> typeArr;
    Array<uint32_t> nameArr;

    for(int i = 0; i < propertiesCount; i++)
    {
        std::string type;
        std::string name;
        input>>type;
        input>>name;

        StringId nameId(name.c_str());
        nameArr.Add(*nameId);

        if(type.compare("int")==0)
        {
            int value;
            input>>value;
            MaterialParameterUnion data;
            data.Int = value;
            dataArr.Add(data);
            typeArr.Add(0);
        }
        else if(type.compare("float")==0)
        {
            float value;
            input>>value;
            MaterialParameterUnion data;
            data.Float = value;
            dataArr.Add(data);
            typeArr.Add(1);
        }
        else if(type.compare("vec3")==0)
        {
            Float3 value;
            input>>value.X>>value.Y>>value.Z;
            MaterialParameterUnion data;
            data.Vec3 = value;
            dataArr.Add(data);
            typeArr.Add(2);
        }
        else if(type.compare("vec4")==0)
        {
            Float4 value;
            input>>value.X>>value.Y>>value.Z>>value.W;
            MaterialParameterUnion data;
            data.Vec4 = value;
            dataArr.Add(data);
            typeArr.Add(3);
        }
        else if(type.compare("mat3")==0)
        {
            Matrix3x3 value;
            input>>value.Column[0].X>>value.Column[0].Y>>value.Column[0].Z;
            input>>value.Column[1].Z>>value.Column[1].Z>>value.Column[1].Z;
            input>>value.Column[2].Z>>value.Column[2].Z>>value.Column[2].Z;
            MaterialParameterUnion data;
            data.Mat3 = value;
            dataArr.Add(data);
            typeArr.Add(4);
        }
        else if(type.compare("mat4")==0)
        {
            Matrix4x4 value;
            input>>value.Column[0].X>>value.Column[0].Y>>value.Column[0].Z>>value.Column[0].W;
            input>>value.Column[1].Z>>value.Column[1].Z>>value.Column[1].Z>>value.Column[1].W;
            input>>value.Column[2].Z>>value.Column[2].Z>>value.Column[2].Z>>value.Column[2].W;
            input>>value.Column[3].Z>>value.Column[3].Z>>value.Column[3].Z>>value.Column[3].W;
            MaterialParameterUnion data;
            data.Mat4 = value;
            dataArr.Add(data);
            typeArr.Add(5);
        }
        if(type.compare("tex")==0)
        {
            std::string value;
            input>>value;
            MaterialParameterUnion data;
            StringId id(value.c_str());
            data.Texture = *id;
            dataArr.Add(data);
            typeArr.Add(6);
        }
    }

    input.close();

    uint32_t byteSize = 0;
    byteSize += sizeof(uint32_t); // shader id
    byteSize += sizeof(uint8_t); // shader id
    byteSize += sizeof(uint32_t); // properties count
    for(int i = 0; i < dataArr.Length(); i++)
    {
        byteSize += sizeof(uint32_t); // name
        byteSize += sizeof(uint32_t); // type
        switch(typeArr[i])
        {
            case 0:
                byteSize += sizeof(int);
                break;
            case 1:
                byteSize += sizeof(float);
                break;
            case 2:
                byteSize += sizeof(Float3);
                break;
            case 3:
                byteSize += sizeof(Float4);
                break;
            case 4:
                byteSize += sizeof(Matrix3x3);
                break;
            case 5:
                byteSize += sizeof(Matrix4x4);
                break;
            case 6:
                byteSize += sizeof(uint32_t);
                break;
        }
    }

    uint8_t* Data = new uint8_t[byteSize];
    int index = 0;

    StringId shaderId = StringId(shaderName.c_str());
    ByteOperations::WriteUint32(Data, &index, *shaderId);
    ByteOperations::WriteUint8(Data, &index, (depthTest=='t')?1:0);
    ByteOperations::WriteUint32(Data, &index, (uint32_t)propertiesCount);

    for(int i = 0; i < dataArr.Length(); i++)
    {
        ByteOperations::WriteUint32(Data, &index, nameArr[i]);
        ByteOperations::WriteUint32(Data, &index, typeArr[i]);
        switch(typeArr[i])
        {
            case 0:
                ByteOperations::WritePtr(Data, &index, (uint8_t*)&dataArr[i].Int, sizeof(int));
                break;
            case 1:
                ByteOperations::WritePtr(Data, &index, (uint8_t*)&dataArr[i].Float, sizeof(float));
                break;
            case 2:
                ByteOperations::WritePtr(Data, &index, (uint8_t*)&dataArr[i].Vec3, sizeof(Float3));
                break;
            case 3:
                ByteOperations::WritePtr(Data, &index, (uint8_t*)&dataArr[i].Vec4, sizeof(Float4));
                break;
            case 4:
                ByteOperations::WritePtr(Data, &index, (uint8_t*)&dataArr[i].Mat3, sizeof(Matrix3x3));
                break;
            case 5:
                ByteOperations::WritePtr(Data, &index, (uint8_t*)&dataArr[i].Mat4, sizeof(Matrix4x4));
                break;
            case 6:
                ByteOperations::WritePtr(Data, &index, (uint8_t*)&dataArr[i].Texture, sizeof(uint32_t));
                break;
        }
    }

	std::stringstream outputPath;
    std::string path = FilePath;
	outputPath << path.substr(0, path.find(".") + 1);
	outputPath << "he";
	std::ofstream output(outputPath.str(), std::ios::binary);

    uint32_t resourceId = *GetName();
    output.write((char*)&resourceId, sizeof(uint32_t));
    output.write((char*)&byteSize, sizeof(uint32_t));
    output.write((char*)Data, byteSize * sizeof(uint8_t));

    output.close();

    delete[] Data;
}