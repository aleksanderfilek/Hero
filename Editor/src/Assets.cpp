#include"Assets.hpp"
#include"Interpreter.hpp"

#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<vector>
#include<set>
#include<utility>
#include<iterator>

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
  size_t uniformPosition = content.find("uniform");
  while(uniformPosition != std::string::npos)
  {
    size_t spaceDelimiter = content.find(" ", uniformPosition) + 1;
    spaceDelimiter = content.find(" ", spaceDelimiter) + 1;
    size_t semicolonDelimiter = content.find(";", spaceDelimiter);

    std::string name = content.substr(spaceDelimiter, semicolonDelimiter - spaceDelimiter);
    uniformNames.push_back(name);

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

  std::stringstream newPath;
  newPath<<cmd.args[0].substr(0, cmd.args[0].find(".") + 1);
  newPath<<"he";
  std::ofstream output(newPath.str(), std::ios::binary);

  uint32_t uniformNumber = uniformNames.size();
  output.write((char*)&uniformNumber, sizeof(uint32_t));
  for(auto uniform: uniformNames)
  {
    uint32_t size = uniform.length();
    output.write((char*)&size, sizeof(uint32_t));
    output.write(uniform.c_str(), size * sizeof(char));
  }

  uint16_t flags = 0;
  for(int i = 0; i < 5; i++)
  {
    if(shaders[i].length() > 0)
    {
      flags |= 1 << i;
    }
  }
  output.write((char*)&flags, sizeof(uint16_t));

  for(int i = 0; i < 5; i++)
  {
    if(flags & 1<<i)
    {
      uint32_t size = shaders[i].length();
      output.write((char*)&size, sizeof(uint32_t));
      output.write(shaders[i].c_str(), size * sizeof(char));
    }
  }

  output.close();
}

static int objMesh(const std::string& path);
void mesh(const Cmd& cmd)
{
  size_t extPos = cmd.args[0].find_last_of(".") + 1;
  std::string ext = cmd.args[0].substr(extPos);
  if(ext.compare("obj")==0)
  {
    objMesh(cmd.args[0]);
  }
}

static int objMesh(const std::string& path)
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

  std::cout<<"Unique vertices: "<<faceSet.size()<<std::endl;
  std::cout<<"All vertices: "<<faces.size()<<std::endl;

  std::vector<float> outPositions;
  std::vector<float> outUVs;
  std::vector<float> outNormals;
  std::vector<int> outIndices;

  // for(auto str: faces)
  // {
  //   std::stringstream line(str);

  //   int posID, uvID, normID;
  //   char delimiter;
  //   line>>posID>>delimiter>>uvID>>delimiter>>normID;
  //   posID -= 1;
  //   uvID -= 1;
  //   normID -= 1;

  //   outPositions.push_back(positions[3*posID + 0]);
  //   outPositions.push_back(positions[3*posID + 1]);
  //   outPositions.push_back(positions[3*posID + 2]);

  //   outUVs.push_back(uvs[2*uvID + 0]);
  //   outUVs.push_back(uvs[2*uvID + 1]);

  //   outNormals.push_back(normals[3*normID + 0]);
  //   outNormals.push_back(normals[3*normID + 1]);
  //   outNormals.push_back(normals[3*normID + 2]);

  //   outIndices.push_back(outIndices.size());
  // }

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

  std::stringstream newPath;
  newPath<<path.substr(0, path.find(".") + 1);
  newPath<<"he";
  std::ofstream output(newPath.str(), std::ios::binary);

  uint32_t nameSize = name.length();
  output.write((char*)&nameSize,sizeof(uint32_t));
  output.write(name.c_str(), name.length() * sizeof(char));

  uint32_t indicesCount = outIndices.size();
  output.write((char*)&indicesCount, sizeof(uint32_t));
  output.write((char*)outIndices.data(), outIndices.size() * sizeof(int));

  uint32_t bufferCount = 3;
  output.write((char*)&bufferCount, sizeof(uint32_t));

  uint8_t positionType = 3;
  output.write((char*)&positionType, sizeof(uint8_t));
  uint32_t positionCount = outPositions.size();
  output.write((char*)&positionCount, sizeof(uint32_t));
  output.write((char*)outPositions.data(), outPositions.size() * sizeof(float));

  uint8_t uvType = 2;
  output.write((char*)&uvType, sizeof(uint8_t));
  uint32_t uvsCount = outUVs.size();
  output.write((char*)&uvsCount, sizeof(uint32_t));
  output.write((char*)outUVs.data(), outUVs.size() * sizeof(float));

  uint8_t normalType = 3;
  output.write((char*)&normalType, sizeof(uint8_t));
  uint32_t normalCount = outNormals.size();
  output.write((char*)&normalCount, sizeof(uint32_t));
  output.write((char*)outNormals.data(), outNormals.size() * sizeof(float));

  output.close();

  return 0;
}

}