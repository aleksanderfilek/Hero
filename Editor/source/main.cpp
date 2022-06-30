#include<iostream>

#include"Interpreter.hpp"
#include"Assets.hpp"
#include"Hero/Systems/Resources.hpp"
#include"Hero/Systems/Window.hpp"

Hero::Resources* resources;

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
      case CmdType::MESH:
        mesh(cmd);
      break;
      case CmdType::SPRITESHEET:
        spritesheet(cmd);
      break;
      case CmdType::TEXTURE:
        texture(cmd);
      break;
      default:
        std::cout<<"Unknown command!"<<std::endl;
      break;
    }
  }
}

}

int WinMain(int argc, char *argv[])
{
  Hero::System::Window* window = new Hero::System::Window(SID("Window"),"Editor",64,64);
  resources = new Hero::Resources(SID("Res"));
  Editor::Interpreter interpreter;

  std::cout<<"Hero Text Editor"<<std::endl;
  Editor::run();

  delete resources;
  delete window;

  return 0;
}