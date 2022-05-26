#include<iostream>

#include"Hero/Core/Core.hpp"
#include"Hero/Systems/Window.hpp"
#include"Hero/Systems/Event.hpp"
#include"Hero/Systems/Input.hpp"
#include"Hero/Systems/Scene.hpp"
#include"Hero/Systems/UserInterface.hpp"
#include"Hero/Systems/Profiler.hpp"

#include"Scenes/Menu.hpp"

#include<cmath>

Hero::Core* core;

event(close)
{
  Hero::Core::close();
}

int WinMain(int argc, char* argv[])
{
  core = new Hero::Core();

  core->addSystem(new Hero::System::Profiler(SID("Profiler"), 2048));
  core->addSystem(new Hero::System::Window(SID("Window"), "Example", 1280, 720));
  core->addSystem(new Hero::System::Event(SID("event")));
  core->addSystem(new Hero::System::Input(SID("input")));
  core->addSystem(new Hero::System::UserInterface(SID("ui"),SID("Window"),SID("input")));
  core->addSystem(new Hero::System::Scene(SID("scene"), new Menu()));

  Hero::System::Event* event = core->getSystem<Hero::System::Event>(SID("event"));
  Hero::System::Window* window = core->getSystem<Hero::System::Window>(SID("Window"));
  window->setEvent(Hero::System::WindowEventType::CLOSE, close);
  event->addWindow(window);

  core->start();

  delete core;

  return 0;
}