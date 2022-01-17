#include<iostream>

#include"Interpreter.hpp"
#include"Assets.hpp"

namespace Editor
{

void run()
{
  bool quit = false;
  while(!quit)
  {
    std::string command;
    std::cout<<"Cmd: ";
    std::getline(std::cin, command);
    
    Cmd cmd = Interpreter::interpret(command);

    switch(cmd.type)
    {
      case CmdType::QUIT:
        quit = true;
      break;
      case CmdType::SHADER:
        shader(cmd);
      break;
      default:
        std::cout<<"Unknown command!"<<std::endl;
      break;
    }
  }
}

}

int main()
{
  Editor::Interpreter interpreter;

  std::cout<<"Hero Text Editor"<<std::endl;
  Editor::run();

  return 0;
}