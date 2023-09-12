#include "MeshConverter.h"
#include "../../../Utility/ByteOperations.h"
#include "../../../Containers/Set.h"
#include "../../../Math/Float3.h"
#include <fstream>
#include <sstream>
#include <string>
#include <set>

void MeshConverter::GetAcceptableExtensions(Array<String>& Extensions)
{
    Extensions.Add("obj");
}

void MeshConverter::Convert(const String& FilePath)
{
    std::string path = *FilePath;
    String extension(path.substr(path.find_last_of(".") + 1).c_str());
    if(extension == "obj")
    {
        ConvertObj(FilePath);
    }
}

void MeshConverter::ConvertObj(const String& FilePath)
{
    std::string name;
    Array<float> positions;
    Array<float> uvs;
    Array<float> normals;
    bool smoothShading = true;
    Array<std::string> faces;
    std::set<std::string> faceSet;

    std::stringstream ssContent;
    std::string content;
    size_t newLinePos = 0;
    size_t startPos = 0;
    std::string cell;

    std::ifstream input(*FilePath);
    ssContent << input.rdbuf();
    input.close();

    content = ssContent.str();

    while((newLinePos = content.find("\n", startPos)) != std::string::npos)
    {
        newLinePos++;
        std::stringstream line(content.substr(startPos, newLinePos - startPos));
        startPos = newLinePos;

        line>>cell;
        if(cell.compare("#") == 0)
        {
            continue;
        }
        else if(cell.compare("o") == 0)
        {
            line>>name;
        }
        else if(cell.compare("v") == 0)
        {
            float posX, posY, posZ;
            line>>posX>>posY>>posZ;

            positions.Add(posX);
            positions.Add(posY);
            positions.Add(posZ);
        }
        else if(cell.compare("vt") == 0)
        {
            float u, v;
            line>>u>>v;
            
            uvs.Add(u);
            uvs.Add(v);
        }
        else if(cell.compare("vn") == 0)
        {
            float nX, nY, nZ;
            line>>nX>>nY>>nZ;

            normals.Add(nX);
            normals.Add(nY);
            normals.Add(nZ);
        }
        else if(cell.compare("s") == 0)
        {
            std::string state;
            line>>state;
            if(state.compare("off") == 0)
            {
            smoothShading = false;
            }
        }
        else if(cell.compare("f") == 0)
        {
            for(int i = 0; i < 3; i++)
            {
            std::string state;
            line>>state;
            auto result = faceSet.insert(state);
            faces.Add(state);
            }
        }
    }

    Array<float> outPositions;
    Array<float> outUVs;
    Array<float> outNormals;
    Array<int> outIndices;

    for(auto str: faceSet)
    {
        std::stringstream line(str);

        int posID, uvID, normID;
        char delimiter;
        line>>posID>>delimiter>>uvID>>delimiter>>normID;
        posID -= 1;
        uvID -= 1;
        normID -= 1;
        outPositions.Add(positions[3*posID + 0]);
        outPositions.Add(positions[3*posID + 1]);
        outPositions.Add(positions[3*posID + 2]);

        outUVs.Add(uvs[2*uvID + 0]);
        outUVs.Add(uvs[2*uvID + 1]);

        outNormals.Add(normals[3*normID + 0]);
        outNormals.Add(normals[3*normID + 1]);
        outNormals.Add(normals[3*normID + 2]);
    }

    for(auto str: faces)
    {
        std::set<std::string>::iterator it;
        int index = 0;
        for(it = faceSet.begin(); it != faceSet.end(); ++it, index++)
        {
            if(str.compare(*it) == 0)
            {
                break;
            }
        }
        outIndices.Add(index);
    }

    Array<float> tangent;
    // if(tangentGen > 0)
    // {
    for(int i = 0; i < faceSet.size(); i++)
    {
        float edge1x = outPositions[3*(i + 1) + 0] - outPositions[3*(i + 0) + 0];
        float edge1y = outPositions[3*(i + 1) + 1] - outPositions[3*(i + 0) + 1];
        float edge1z = outPositions[3*(i + 1) + 2] - outPositions[3*(i + 0) + 2];

        float edge2x = outPositions[3*(i + 2) + 0] - outPositions[3*(i + 0) + 0];
        float edge2y = outPositions[3*(i + 2) + 1] - outPositions[3*(i + 0) + 1];
        float edge2z = outPositions[3*(i + 2) + 2] - outPositions[3*(i + 0) + 2];

        float deltaUV1x = outUVs[2*(i + 1) + 0] - outUVs[2*(i + 0) + 0];
        float deltaUV1y = outUVs[2*(i + 1) + 1] - outUVs[2*(i + 0) + 1];

        float deltaUV2x = outUVs[2*(i + 2) + 0] - outUVs[2*(i + 0) + 0];
        float deltaUV2y = outUVs[2*(i + 2) + 1] - outUVs[2*(i + 0) + 1];

        float f = 1.0f / (deltaUV1x * deltaUV2y - deltaUV2x * deltaUV1y);

        float tangentx = f * (deltaUV2y * edge1x - deltaUV1y * edge2x);
        float tangenty = f * (deltaUV2y * edge1y - deltaUV1y * edge2y);
        float tangentz = f * (deltaUV2y * edge1z - deltaUV1y * edge2z);

        Float3 tangentV(tangentx,tangenty,tangentz);

        if(tangentV.Length() == 0.0f)
        {
        //std::cout<<"tangent error\n";
        // std::cout<<"\tdeltaUV2y "<<deltaUV2y<<" deltaUV1y "<<deltaUV1y<<std::endl;
        // std::cout<<"\tedge1 "<<edge1x<<" "<<edge1y<<" "<<edge1z<<std::endl;
        // std::cout<<"\tedge2 "<<edge2x<<" "<<edge2y<<" "<<edge2z<<std::endl;
        }
        tangentV.Normalize();

        for(int j = 0; j < 3; j++)
        {
            tangent.Add(tangentV.X);
            tangent.Add(tangentV.Y);
            tangent.Add(tangentV.Z);
        }
    }
    //}

    uint32_t byteSize = 0;
    byteSize += sizeof(uint32_t);
    byteSize += outIndices.Length() * sizeof(int);
    byteSize += sizeof(uint32_t);
    byteSize += sizeof(uint8_t);
    byteSize += sizeof(uint32_t);
    byteSize += outPositions.Length() * sizeof(float);
    byteSize += sizeof(uint8_t);
    byteSize += sizeof(uint32_t);
    byteSize += outUVs.Length() * sizeof(float);
    byteSize += sizeof(uint8_t);
    byteSize += sizeof(uint32_t);
    byteSize += outNormals.Length() * sizeof(float);
    // if(tangentGen > 0)
    // {
    byteSize += sizeof(uint8_t);
    byteSize += sizeof(uint32_t);
    byteSize += tangent.Length() * sizeof(float);
    //}

    int Iptr = 0;
    uint8_t* Data = new uint8_t[byteSize];
    ByteOperations::WriteUint32(Data, &Iptr, outIndices.Length());
    ByteOperations::WritePtr(Data, &Iptr, (uint8_t*)outIndices.Data(), outIndices.Length() * sizeof(int));
    uint32_t bufferCount = 3;
    // if(tangentGen > 0)
    // {
    bufferCount += 1;
    //}
    ByteOperations::WriteUint32(Data, &Iptr, bufferCount);
    uint8_t positionType = 3;
    ByteOperations::WriteUint8(Data, &Iptr, positionType);
    ByteOperations::WriteUint32(Data, &Iptr, outPositions.Length() * sizeof(float));
    ByteOperations::WritePtr(Data, &Iptr, (uint8_t*)outPositions.Data(), outPositions.Length() * sizeof(float));
    uint8_t uvType = 2;
    ByteOperations::WriteUint8(Data, &Iptr, uvType);
    ByteOperations::WriteUint32(Data, &Iptr, outUVs.Length() * sizeof(float));
    ByteOperations::WritePtr(Data, &Iptr, (uint8_t*)outUVs.Data(), outUVs.Length() * sizeof(float));
    uint8_t normalType = 3;
    ByteOperations::WriteUint8(Data, &Iptr, normalType);
    ByteOperations::WriteUint32(Data, &Iptr, outNormals.Length() * sizeof(float));
    ByteOperations::WritePtr(Data, &Iptr, (uint8_t*)outNormals.Data(), outNormals.Length() * sizeof(float));
    // if(tangentGen > 0)
    // {
    uint8_t tangentType = 3;
    ByteOperations::WriteUint8(Data, &Iptr, tangentType);
    ByteOperations::WriteUint32(Data, &Iptr, tangent.Length() * sizeof(float));
    ByteOperations::WritePtr(Data, &Iptr, (uint8_t*)tangent.Data(), tangent.Length() * sizeof(float));
    //}

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