#include"Assets.hpp"
#include"Interpreter.hpp"

#include"Hero/Utility/Qoi.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include"Hero/ThirdParty/Stb/stb_image.h"
#include"Hero/Graphics/Texture.hpp"
#include"Hero/Graphics/Cubemap.hpp"
#include"Hero/Core/Math.hpp"
#include"Hero/Graphics/Material.hpp"

#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<vector>
#include<set>
#include<utility>
#include<iterator>

#include"Hero/Graphics/Shader.hpp"
#include"Hero/Systems/Resources.hpp"
#include"Hero/Utility/ByteOperations.hpp"

extern Hero::Resources* resources;

namespace Editor
{

void shader(const Cmd& cmd)
{
  if(cmd.args.size() != 1)
  {
    std::cout<<"Too many or too few arguments"<<std::endl;
    return;
  }

  const std::string& path = cmd.args[0];

  std::ifstream input(path);
  std::stringstream sContent;
  sContent << input.rdbuf();
  std::string content = sContent.str();
  input.close();

  std::vector<std::string> uniformNames;
  std::vector<std::string> textureNames;

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
      // for(int i = 1; i < 5; i++)
      // {
      //   size_t next = content.find(endOfUniform[i], secondSpaceDelimiter);
      //   if(next < semicolonDelimiter) 
      //     semicolonDelimiter = next;
      // }

      std::string name = content.substr(secondSpaceDelimiter + 1, semicolonDelimiter - secondSpaceDelimiter - 1);
      if(isTexture)
      {
        textureNames.push_back(name);
      }
      else
      {
        uniformNames.push_back(name);
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

  uint32_t uniformNumber = uniformNames.size();
  Hero::WriteUint32(Data, &index, uniformNumber);
  for(auto uniform: uniformNames)
  {
    uint32_t size = uniform.length();
    Hero::WriteUint32(Data, &index, size);
    Hero::WritePtr(Data, &index, (uint8_t*)uniform.c_str(),size * sizeof(char));
  }

  uint32_t textureUniformNumber = textureNames.size();
  Hero::WriteUint32(Data, &index, textureUniformNumber);
  for(auto uniform: textureNames)
  {
    uint32_t size = uniform.length();
    Hero::WriteUint32(Data, &index, size);
    Hero::WritePtr(Data, &index, (uint8_t*)uniform.c_str(),size * sizeof(char));
  }

  Hero::WriteUint16(Data, &index, flags);
  for(int i = 0; i < 5; i++)
  {
    if(flags & 1<<i)
    {
      uint32_t size = shaders[i].length();
      Hero::WriteUint32(Data, &index, size);
      Hero::WritePtr(Data, &index, (uint8_t*)shaders[i].c_str(), size * sizeof(char));
    }
  }

  std::stringstream newPath;
  newPath<<cmd.args[0].substr(0, cmd.args[0].find(".") + 1);
  newPath<<"he";
  std::ofstream output(newPath.str(), std::ios::binary);

  int resourceId = Hero::Shader::GetId();
  output.write((char*)&resourceId, sizeof(int));
  std::cout<<"size "<<byteSize<<std::endl;
  output.write((char*)&byteSize, sizeof(uint32_t));
  output.write((char*)Data, byteSize * sizeof(uint8_t));
  output.close();

  delete[] Data;

  std::string pathStr = newPath.str();
  resources->Add(SID("Shader"), pathStr);
}

static int objMesh(const std::string& path, int tangentGen);
void mesh(const Cmd& cmd)
{
  size_t extPos = cmd.args[0].find_last_of(".") + 1;
  std::string ext = cmd.args[0].substr(extPos);
  if(ext.compare("obj")==0)
  {
    objMesh(cmd.args[0], stoi(cmd.args[1]));
  }
}

static int objMesh(const std::string& path, int tangentGen)
{

  std::string name;
  std::vector<float> positions;
  std::vector<float> uvs;
  std::vector<float> normals;
  bool smoothShading = true;
  std::vector<std::string> faces;
  std::set<std::string> faceSet;

  std::stringstream ssContent;
  std::string content;
  size_t newLinePos = 0;
  size_t startPos = 0;
  std::string cell;

  std::ifstream input(path);
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

      positions.push_back(posX);
      positions.push_back(posY);
      positions.push_back(posZ);
    }
    else if(cell.compare("vt") == 0)
    {
      float u, v;
      line>>u>>v;
      
      uvs.push_back(u);
      uvs.push_back(v);
    }
    else if(cell.compare("vn") == 0)
    {
      float nX, nY, nZ;
      line>>nX>>nY>>nZ;

      normals.push_back(nX);
      normals.push_back(nY);
      normals.push_back(nZ);
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
        faces.push_back(state);
      }
    }
  }

  std::vector<float> outPositions;
  std::vector<float> outUVs;
  std::vector<float> outNormals;
  std::vector<int> outIndices;

  for(auto str: faceSet)
  {
    std::stringstream line(str);

    int posID, uvID, normID;
    char delimiter;
    line>>posID>>delimiter>>uvID>>delimiter>>normID;
    posID -= 1;
    uvID -= 1;
    normID -= 1;
    outPositions.push_back(positions[3*posID + 0]);
    outPositions.push_back(positions[3*posID + 1]);
    outPositions.push_back(positions[3*posID + 2]);

    outUVs.push_back(uvs[2*uvID + 0]);
    outUVs.push_back(uvs[2*uvID + 1]);

    outNormals.push_back(normals[3*normID + 0]);
    outNormals.push_back(normals[3*normID + 1]);
    outNormals.push_back(normals[3*normID + 2]);
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
    outIndices.push_back(index);
  }

  std::vector<float> tangent;
  std::vector<float> bitangent;
  if(tangentGen > 0)
  {
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

      float bitangentx = f * (-deltaUV2x * edge1x + deltaUV1x * edge2x);
      float bitangenty = f * (-deltaUV2x * edge1y + deltaUV1x * edge2y);
      float bitangentz = f * (-deltaUV2x * edge1z + deltaUV1x * edge2z);

      Hero::Float3 tangentV(tangentx,tangenty,tangentz);
      Hero::Float3 bitangentV(bitangentx,bitangenty,bitangentz);

      tangentV.normalize();
      bitangentV.normalize();

      for(int j = 0; j < 3; j++)
      {
        tangent.push_back(tangentV.x);
        tangent.push_back(tangentV.x);
        tangent.push_back(tangentV.x);

        bitangent.push_back(bitangentV.x);
        bitangent.push_back(bitangentV.y);
        bitangent.push_back(bitangentV.z);
      }
    }
  }

  uint32_t byteSize = 0;
  byteSize += sizeof(uint32_t);
  byteSize += outIndices.size() * sizeof(int);
  byteSize += sizeof(uint32_t);
  byteSize += sizeof(uint8_t);
  byteSize += sizeof(uint32_t);
  byteSize += outPositions.size() * sizeof(float);
  byteSize += sizeof(uint8_t);
  byteSize += sizeof(uint32_t);
  byteSize += outUVs.size() * sizeof(float);
  byteSize += sizeof(uint8_t);
  byteSize += sizeof(uint32_t);
  byteSize += outNormals.size() * sizeof(float);
  if(tangentGen > 0)
  {
  byteSize += sizeof(uint8_t);
  byteSize += sizeof(uint32_t);
  byteSize += tangent.size() * sizeof(float);
  byteSize += sizeof(uint8_t);
  byteSize += sizeof(uint32_t);
  byteSize += bitangent.size() * sizeof(float);
  }

  int Iptr = 0;
  uint8_t* Data = new uint8_t[byteSize];
  Hero::WriteUint32(Data, &Iptr, outIndices.size());
  Hero::WritePtr(Data, &Iptr, (uint8_t*)outIndices.data(), outIndices.size() * sizeof(int));
  uint32_t bufferCount = 3;
  if(tangentGen > 0)
  {
    bufferCount += 2;
  }
  Hero::WriteUint32(Data, &Iptr, bufferCount);
  uint8_t positionType = 3;
  Hero::WriteUint8(Data, &Iptr, positionType);
  Hero::WriteUint32(Data, &Iptr, outPositions.size() * sizeof(float));
  Hero::WritePtr(Data, &Iptr, (uint8_t*)outPositions.data(), outPositions.size() * sizeof(float));
  uint8_t uvType = 2;
  Hero::WriteUint8(Data, &Iptr, uvType);
  Hero::WriteUint32(Data, &Iptr, outUVs.size() * sizeof(float));
  Hero::WritePtr(Data, &Iptr, (uint8_t*)outUVs.data(), outUVs.size() * sizeof(float));
  uint8_t normalType = 3;
  Hero::WriteUint8(Data, &Iptr, normalType);
  Hero::WriteUint32(Data, &Iptr, outNormals.size() * sizeof(float));
  Hero::WritePtr(Data, &Iptr, (uint8_t*)outNormals.data(), outNormals.size() * sizeof(float));
  if(tangentGen > 0)
  {
    uint8_t tangentType = 3;
    Hero::WriteUint8(Data, &Iptr, tangentType);
    Hero::WriteUint32(Data, &Iptr, tangent.size() * sizeof(float));
    Hero::WritePtr(Data, &Iptr, (uint8_t*)tangent.data(), tangent.size() * sizeof(float));
    uint8_t bitangentType = 3;
    Hero::WriteUint8(Data, &Iptr, bitangentType);
    Hero::WriteUint32(Data, &Iptr, bitangent.size() * sizeof(float));
    Hero::WritePtr(Data, &Iptr, (uint8_t*)bitangent.data(), bitangent.size() * sizeof(float));
  }

  std::stringstream newPath;
  newPath<<path.substr(0, path.find(".") + 1);
  newPath<<"he";
  std::ofstream output(newPath.str(), std::ios::binary);

  int ResourceId = Hero::Mesh::GetId();
  std::cout<<"ID "<<ResourceId<<std::endl;
  output.write((char*)&ResourceId, sizeof(int));
  output.write((char*)&byteSize, sizeof(uint32_t));
  output.write((char*)Data, byteSize * sizeof(uint8_t));

  output.close();

  delete[] Data;

  std::cout<<"saved"<<std::endl;

  std::string pathStr = newPath.str();
  resources->Add(SID("mesh"), pathStr);

  return 0;
}

void spritesheet(const Cmd& cmd)
{
  const std::string path(cmd.args[0]);
  std::stringstream content;

  std::ifstream input(path);
  content << input.rdbuf();
  input.close();

  struct Sprite
  {
    std::string name;
    uint32_t x,y,w,h;
  };
  std::string texturePath;
  std::vector<Sprite> sprites;
  content>>texturePath;

  while(!content.eof())
  {
    Sprite sprite;

    content>>sprite.name>>sprite.x>>sprite.y>>sprite.w>>sprite.h;

    sprites.push_back(sprite);
  }

  std::stringstream newPath;
  newPath<<path.substr(0, path.find(".") + 1);
  newPath<<"he";
  std::ofstream output(newPath.str(), std::ios::binary);

  uint32_t texturePathSize = texturePath.length();
  output.write((char*)&texturePathSize, sizeof(uint32_t));
  output.write(texturePath.c_str(), texturePathSize*sizeof(char));

  uint32_t spritesCount = sprites.size();
  output.write((char*)&spritesCount, sizeof(uint32_t));
  for(auto sprite: sprites)
  {
    uint32_t spriteNameSize = sprite.name.length();
    output.write((char*)&spriteNameSize, sizeof(uint32_t));
    output.write(sprite.name.c_str(), spriteNameSize*sizeof(char));
    output.write((char*)&sprite.x, sizeof(uint32_t));
    output.write((char*)&sprite.y, sizeof(uint32_t));
    output.write((char*)&sprite.w, sizeof(uint32_t));
    output.write((char*)&sprite.h, sizeof(uint32_t));
  }

  output.close();
}

void texture(const Cmd& cmd)
{
  int width, height, nrChannels;
  uint32_t ByteLength = 0;
  uint8_t *data = stbi_load(cmd.args[0].c_str(), &width, &height, &nrChannels, 0); 

  uint8_t* encoded = Hero::QOI::Encode(data, (uint32_t)width, (uint32_t)height, (uint8_t)nrChannels, ByteLength);

  stbi_image_free(data);

  uint8_t channels = (uint8_t)nrChannels;
  uint8_t colorSpace = (uint8_t)Hero::ColorSpace::Linear;
  uint8_t flags = (uint8_t)Hero::TextureFlag::LINEAR | (uint8_t)Hero::TextureFlag::MIPMAP;

  uint32_t byteSize = 0;
  byteSize += sizeof(int);
  byteSize += sizeof(int);
  byteSize += sizeof(uint8_t);
  byteSize += sizeof(uint8_t);
  byteSize += sizeof(uint8_t);
  byteSize += sizeof(uint32_t);
  byteSize += ByteLength * sizeof(uint8_t);

  uint8_t* Data = new uint8_t[byteSize];
  int index = 0;
  Hero::WriteInt(Data, &index, width);
  Hero::WriteInt(Data, &index, height);
  Hero::WriteUint8(Data, &index, channels);
  Hero::WriteUint8(Data, &index, colorSpace);
  Hero::WriteUint8(Data, &index, flags);
  Hero::WriteUint32(Data, &index, ByteLength);
  Hero::WritePtr(Data, &index, encoded, ByteLength * sizeof(uint8_t));

  delete[] encoded;

  std::stringstream newPath;
  newPath<<cmd.args[0].substr(0, cmd.args[0].find(".") + 1);
  newPath<<"he";
  std::ofstream output(newPath.str(), std::ios::binary);

  int ResourceId = Hero::Texture::GetId();
  output.write((char*)&ResourceId, sizeof(int));
  output.write((char*)&byteSize, sizeof(uint32_t));
  output.write((char*)Data, byteSize * sizeof(uint8_t));

  output.close();

  delete[] Data;

  std::string pathStr = newPath.str();
  resources->Add(SID("Texture"), pathStr);

}

void cubemap(const Cmd& cmd)
{
  if(cmd.args.size() != 6)
  {
    std::cout<<"Too many or too few arguments. Six required!"<<std::endl;
    return;
  }

  int width, height, channels;
  std::vector<uint32_t> byteLengths;
  std::vector<uint8_t*> images;

  for(int i = 0; i < cmd.args.size(); i++)
  {
    uint32_t ByteLength = 0;
    uint8_t *data = stbi_load(cmd.args[i].c_str(), &width, &height, &channels, 0); 

    uint8_t* encoded = Hero::QOI::Encode(data, (uint32_t)width, (uint32_t)height, (uint8_t)channels, ByteLength);
    std::cout<<ByteLength<<std::endl;
    stbi_image_free(data);

    byteLengths.push_back(ByteLength);
    images.push_back(encoded);
  }

  uint32_t byteSize = 0;
  byteSize += sizeof(int);
  byteSize += sizeof(int);
  byteSize += sizeof(uint8_t);
  for(int i = 0; i < cmd.args.size(); i++)
  {
    byteSize += sizeof(uint32_t);
    byteSize += byteLengths[i];
  }

  uint8_t* Data = new uint8_t[byteSize];
  int index = 0;
  Hero::WriteInt(Data, &index, width);
  Hero::WriteInt(Data, &index, height);
  Hero::WriteUint8(Data, &index, (uint8_t)channels);
  for(int i = 0; i < cmd.args.size(); i++)
  {
    Hero::WriteUint32(Data, &index, byteLengths[i]);
    Hero::WritePtr(Data, &index, images[i], byteLengths[i]);
  }

  std::stringstream newPath;
  newPath<<cmd.args[0].substr(0, cmd.args[0].find(".") + 1);
  newPath<<"he";
  std::ofstream output(newPath.str(), std::ios::binary);

  int ResourceId = Hero::Cubemap::GetId();
  output.write((char*)&ResourceId, sizeof(int));
  output.write((char*)&byteSize, sizeof(uint32_t));
  output.write((char*)Data, byteSize * sizeof(uint8_t));

  output.close();

  delete[] Data;

  for(int i = 0; i < cmd.args.size(); i++)
  {
    delete[] images[i];
  }

  std::string pathStr = newPath.str();
  resources->Add(SID("Cubemap"), pathStr);
}

void material(const Cmd& cmd)
{
  if(cmd.args.size() != 1)
  {
    std::cout<<"Too many or too few arguments"<<std::endl;
    return;
  }

  const std::string& path = cmd.args[0];

  std::string shaderName;
  int propertiesCount = 0;

  std::ifstream input(path);

  input>>shaderName;
  input>>propertiesCount;

  union MatData
  {
    int i;
    float f;
    Hero::Float3 vec3;
    Hero::Float4 vec4;
    Hero::Matrix3x3 mat3;
    Hero::Matrix4x4 mat4;
    uint32_t texture;

    MatData(){}
    ~MatData(){}
  };

  std::vector<MatData> dataArr;
  std::vector<uint32_t> typeArr;
  std::vector<uint32_t> nameArr;

  for(int i = 0; i < propertiesCount; i++)
  {
    std::string type;
    std::string name;
    input>>type;
    input>>name;

    Hero::Sid nameSid = SID(name.c_str());
    nameArr.push_back(nameSid.id);

    if(type.compare("int")==0)
    {
      int value;
      input>>value;
      MatData data;
      data.i = value;
      dataArr.push_back(data);
      typeArr.push_back(0);
    }
    else if(type.compare("float")==0)
    {
      float value;
      input>>value;
      MatData data;
      data.f = value;
      dataArr.push_back(data);
      typeArr.push_back(1);
    }
    else if(type.compare("vec3")==0)
    {
      Hero::Float3 value;
      input>>value.x>>value.y>>value.z;
      MatData data;
      data.vec3 = value;
      dataArr.push_back(data);
      typeArr.push_back(2);
    }
    else if(type.compare("vec4")==0)
    {
      Hero::Float4 value;
      input>>value.x>>value.y>>value.z>>value.w;
      MatData data;
      data.vec4 = value;
      dataArr.push_back(data);
      typeArr.push_back(3);
    }
    else if(type.compare("mat3")==0)
    {
      Hero::Matrix3x3 value;
      input>>value.col[0].x>>value.col[0].y>>value.col[0].z;
      input>>value.col[1].z>>value.col[1].z>>value.col[1].z;
      input>>value.col[2].z>>value.col[2].z>>value.col[2].z;
      MatData data;
      data.mat3 = value;
      dataArr.push_back(data);
      typeArr.push_back(4);
    }
    else if(type.compare("mat4")==0)
    {
      Hero::Matrix4x4 value;
      input>>value.col[0].x>>value.col[0].y>>value.col[0].z>>value.col[0].w;
      input>>value.col[1].z>>value.col[1].z>>value.col[1].z>>value.col[1].w;
      input>>value.col[2].z>>value.col[2].z>>value.col[2].z>>value.col[2].w;
      input>>value.col[3].z>>value.col[3].z>>value.col[3].z>>value.col[3].w;
      MatData data;
      data.mat4 = value;
      dataArr.push_back(data);
      typeArr.push_back(5);
    }
    if(type.compare("tex")==0)
    {
      std::string value;
      input>>value;
      MatData data;
      Hero::Sid sid = SID(value.c_str());
      data.texture = sid.id;
      dataArr.push_back(data);
      typeArr.push_back(6);
    }
  }

  input.close();

  uint32_t byteSize = 0;
  byteSize += sizeof(uint32_t); // shader id
  byteSize += sizeof(uint32_t); // properties count
  for(int i = 0; i < dataArr.size(); i++)
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
        byteSize += sizeof(Hero::Float3);
      break;
      case 3:
        byteSize += sizeof(Hero::Float4);
      break;
      case 4:
        byteSize += sizeof(Hero::Matrix3x3);
      break;
      case 5:
        byteSize += sizeof(Hero::Matrix4x4);
      break;
      case 6:
        byteSize += sizeof(uint32_t);
      break;
    }
  }

  uint8_t* Data = new uint8_t[byteSize];
  int index = 0;

  Hero::Sid shaderSid = SID(shaderName.c_str());
  Hero::WriteUint32(Data, &index, shaderSid.id);
  Hero::WriteUint32(Data, &index, (uint32_t)propertiesCount);

  for(int i = 0; i < dataArr.size(); i++)
  {
    Hero::WriteUint32(Data, &index, nameArr[i]);
    Hero::WriteUint32(Data, &index, typeArr[i]);
    switch(typeArr[i])
    {
      case 0:
        Hero::WritePtr(Data, &index, (uint8_t*)&dataArr[i].i, sizeof(int));
      break;
      case 1:
        Hero::WritePtr(Data, &index, (uint8_t*)&dataArr[i].f, sizeof(float));
      break;
      case 2:
        Hero::WritePtr(Data, &index, (uint8_t*)&dataArr[i].vec3, sizeof(Hero::Float3));
      break;
      case 3:
        Hero::WritePtr(Data, &index, (uint8_t*)&dataArr[i].vec4, sizeof(Hero::Float4));
      break;
      case 4:
        Hero::WritePtr(Data, &index, (uint8_t*)&dataArr[i].mat3, sizeof(Hero::Matrix3x3));
      break;
      case 5:
        Hero::WritePtr(Data, &index, (uint8_t*)&dataArr[i].mat4, sizeof(Hero::Matrix4x4));
      break;
      case 6:
        Hero::WritePtr(Data, &index, (uint8_t*)&dataArr[i].texture, sizeof(uint32_t));
      break;
    }
  }

  std::stringstream newPath;
  newPath<<cmd.args[0].substr(0, cmd.args[0].find(".") + 1);
  newPath<<"he";
  std::ofstream output(newPath.str(), std::ios::binary);

  int ResourceId = Hero::Material::GetId();
  output.write((char*)&ResourceId, sizeof(int));
  output.write((char*)&byteSize, sizeof(uint32_t));
  output.write((char*)Data, byteSize * sizeof(uint8_t));

  output.close();

  delete[] Data;
}

}