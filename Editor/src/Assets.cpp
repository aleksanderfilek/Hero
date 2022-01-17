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

  std::ifstream readFile(path);
  std::stringstream sContent;
  sContent << readFile.rdbuf();
  std::string content = sContent.str();

  std::vector<std::string> uniformNames;
  size_t uniformPosition = content.find("uniform");
  while(uniformPosition != std::string::npos)
  {
    size_t spaceDelimiter = content.find(" ");

    uniformNames.push_back(content.substr(uniformPosition, spaceDelimiter - uniformPosition));

    std::cout<<uniformNames[uniformNames.size()-1]<<std::endl;

    uniformPosition = content.find("uniform", spaceDelimiter);
  }


  readFile.close();
}
  
}