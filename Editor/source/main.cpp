#include<iostream>

#include"Interpreter.hpp"
#include"Assets.hpp"
#include"Hero/Systems/Resources.hpp"
#include"Hero/Systems/Window.hpp"
#include"Hero/Core/Core.hpp"

Hero::Resources* resources;

Hero::Core* core;

event(close)
{
  Hero::Core::close();
}

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
    }
  }
}

}

int WinMain(int argc, char *argv[])
{
  core = new Hero::Core();

  Hero::System::Window* window = new Hero::System::Window(SID("Window"),"Editor",64,64);
  resources = new Hero::Resources(SID("Res"));

  core->addSystem(window);
  core->addSystem(resources);

  window->setEvent(Hero::System::WindowEventType::CLOSE, close);

  Editor::Interpreter interpreter;

  std::cout<<"Hero Text Editor"<<std::endl;
  Editor::run();

  return 0;
}