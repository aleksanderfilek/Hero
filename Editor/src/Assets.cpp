#include"Assets.hpp"
#include"Interpreter.hpp"

#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<vector>

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
  
}