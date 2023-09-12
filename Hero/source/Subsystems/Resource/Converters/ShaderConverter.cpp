#include "ShaderConverter.h"
#include "../../../Utility/ByteOperations.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

void ShaderConverter::GetAcceptableExtensions(Array<String>& Extensions)
{
    Extensions.Add("glsl");
}

void ShaderConverter::Convert(const String& FilePath)
{
    std::ifstream input(*FilePath);

    std::stringstream stream;
    stream << input.rdbuf();
    std::string content = stream.str();
    input.close();

    Array<std::string> uniformNames;
    Array<std::string> textureNames;

    size_t uniformPosition = content.find("uniform");
    const char* endOfUniform[] = {";", "[","{","\n"," "};
    const char* acceptableUniformType[] = { "int", "float", "vec3", "vec4", "mat3", "mat4", "sampler2D" };
    while(uniformPosition != std::string::npos)
    {
        size_t spaceDelimiter = content.find(" ", uniformPosition) + 1;
        size_t secondSpaceDelimiter = content.find(" ", spaceDelimiter);
        size_t semicolonDelimiter = secondSpaceDelimiter;
        std::string type = content.substr(spaceDelimiter, secondSpaceDelimiter - spaceDelimiter);

        bool accept = false;
        bool isTexture = false;
        for(int i = 0; i < 7; i++)
        {
            if(type.compare(acceptableUniformType[i]) == 0)
            {
                if(i == 6)
                {
                    isTexture = true;
                }
                accept = true;
                break;
            }
        }

        if(accept)
        {
            semicolonDelimiter = content.find(endOfUniform[0], secondSpaceDelimiter);

            std::string name = content.substr(secondSpaceDelimiter + 1, semicolonDelimiter - secondSpaceDelimiter - 1);
            if(isTexture)
            {
                textureNames.Add(name);
            }
            else
            {
                uniformNames.Add(name);
            }
        }

        uniformPosition = content.find("uniform", semicolonDelimiter);
    }

    std::string shaders[5];
    size_t shaderPos[5];
    shaderPos[0] = content.find("#vertex");
    shaderPos[1] = content.find("#tessControl");
    shaderPos[2] = content.find("#tessEvaluation");
    shaderPos[3] = content.find("#geometry");
    shaderPos[4] = content.find("#fragment");
    int iterator = 0;
    for(int i = 0; i < 5; i++)
    {
        size_t eolDelimiter = content.find("\n", shaderPos[i]) + 1;

        size_t endPos = (i == 4)?std::string::npos:shaderPos[i+1];

        std::string body = content.substr(eolDelimiter, endPos - eolDelimiter - 1);
        shaders[i] = body;
    }

    int index = 0;
    uint32_t byteSize = 0;
    uint8_t* Data = nullptr;

    byteSize += sizeof(uint32_t); // uniform number
    for(auto uniform: uniformNames)
    {
        byteSize += sizeof(uint32_t); // uniform text size
        byteSize += uniform.length() * sizeof(char); // uniform text
    }

    byteSize += sizeof(uint32_t); // texture uniform number
    for(auto uniform: textureNames)
    {
        byteSize += sizeof(uint32_t); // uniform text size
        byteSize += uniform.length() * sizeof(char); // uniform text
    }

    byteSize += sizeof(uint32_t); // flags
    uint16_t flags = 0;
    for(int i = 0; i < 5; i++)
    {
        if(shaders[i].length() > 0)
        {
            flags |= 1 << i;
        }
    }
    
    for(int i = 0; i < 5; i++)
    {
        if(flags & 1<<i)
        {
            byteSize += sizeof(uint32_t); // shader text size
            byteSize += shaders[i].length() * sizeof(char); // shader text
        }
    }

    Data = new uint8_t[byteSize];

    uint32_t uniformNumber = uniformNames.Length();
    ByteOperations::WriteUint32(Data, &index, uniformNumber);
    for(auto uniform: uniformNames)
    {
        uint32_t size = uniform.length();
        ByteOperations::WriteUint32(Data, &index, size);
        ByteOperations::WritePtr(Data, &index, (uint8_t*)uniform.c_str(),size * sizeof(char));
    }

    uint32_t textureUniformNumber = textureNames.Length();
    ByteOperations::WriteUint32(Data, &index, textureUniformNumber);
    for(auto uniform: textureNames)
    {
        uint32_t size = uniform.length();
        ByteOperations::WriteUint32(Data, &index, size);
        ByteOperations::WritePtr(Data, &index, (uint8_t*)uniform.c_str(),size * sizeof(char));
    }

    ByteOperations::WriteUint16(Data, &index, flags);
    for(int i = 0; i < 5; i++)
    {
        if(flags & 1<<i)
        {
            uint32_t size = shaders[i].length();
            ByteOperations::WriteUint32(Data, &index, size);
            ByteOperations::WritePtr(Data, &index, (uint8_t*)shaders[i].c_str(), size * sizeof(char));
        }
    }

	std::stringstream outputPath;
    std::string path = *FilePath;
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