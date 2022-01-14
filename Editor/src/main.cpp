#include<iostream>

#include"Interpreter.hpp"

namespace Editor
{

void run()
{
  bool quit = false;
  while(!quit)
  {
    std::string command;
    std::cout<<"Cmd: ";
    std::cin>>command;
    
    Cmd cmd = Editor::Interpreter::interpret(command);

    switch(cmd.type)
    {
      case Editor::CmdType::QUIT:
        quit = true;
      break;
      default:
        std::cout<<"err"<<std::endl;
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