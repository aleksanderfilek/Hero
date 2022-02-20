#include<iostream>

#include"HeroCore.hpp"
#include"HeroSystems.hpp"

#include"Menu.hpp"

#include<cmath>

Hero::Core* core;

event(close)
{
  Hero::Core::close();
}

int HeroMain(int argc, char* argv[])
{
  core = new Hero::Core();

  core->addSystem(new Hero::System::Window(SID("window"), "Example", 640, 480));
  core->addSystem(new Hero::System::Event(SID("event")));
  core->addSystem(new Hero::System::Input(SID("input")));
  core->addSystem(new Hero::System::UserInterface(SID("ui"),SID("window"),SID("input")));
  core->addSystem(new Hero::System::Scene(SID("scene"), new Menu()));

  Hero::System::Event* event = core->getSystem<Hero::System::Event>(SID("event"));
  Hero::System::Window* window = core->getSystem<Hero::System::Window>(SID("window"));
  window->setEvent(Hero::System::WindowEventType::CLOSE, close);
  event->addWindow(window);

  core->start();

  delete core;

  return 0;
}