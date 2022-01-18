#include<iostream>

#include"Core.hpp"
#include"HeroSystems.hpp"

Hero::Core* core;

event(close)
{
  Hero::Core::close();
}

int SDL_main(int argc, char* argv[])
{
  core = new Hero::Core();

  core->addSystem(new Hero::System::Window(SID("window"), "Example", 640, 480));
  core->addSystem(new Hero::System::Event(SID("event")));
  Hero::System::Event* event = (Hero::System::Event*)core->getSystem(SID("event"));
  Hero::System::Window* window = (Hero::System::Window*)core->getSystem(SID("window"));
  window->setEvent(Hero::System::WindowEventType::CLOSE, close);
  window->setBackgroundColor((Hero::Color){0,255,255,255});
  event->addWindow(window);

  core->start();

  delete core;

  return 0;
}