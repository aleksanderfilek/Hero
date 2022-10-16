#include<iostream>

#include"Hero/Core/Core.hpp"
#include"Hero/Systems/Window.hpp"
#include"Hero/Systems/Event.hpp"
#include"Hero/Systems/Input.hpp"
#include"Hero/Systems/ActorScene/SceneSystem.hpp"
#include"Hero/Systems/UserInterface.hpp"
#include"Hero/Systems/Resources.hpp"

#include"Scenes/Game.hpp"
#include"Systems/Editor.hpp"

Hero::Core* core;

event(close)
{
  Hero::Core::close();
}

int WinMain(int argc, char* argv[])
{
  core = new Hero::Core();

  core->addSystem(new Hero::System::Window(SID("Window"), "Example", 1280, 720));
  core->addSystem(new Hero::System::Event(SID("event")));
  core->addSystem(new Hero::System::Input(SID("input")));
  core->addSystem(new Hero::SceneSystem(SID("scene"), new Game()));
  core->addSystem(new Hero::System::UserInterface(SID("ui"),SID("Window"),SID("input")));
  core->addSystem(new Hero::Resources(SID("resources")));
  core->addSystem(new Editor(SID("Editor")));

  Hero::System::Event* event = core->getSystem<Hero::System::Event>(SID("event"));
  Hero::System::Window* window = core->getSystem<Hero::System::Window>(SID("Window"));
  window->setEvent(Hero::System::WindowEventType::CLOSE, close);
  event->addWindow(window);

  core->start();

  delete core;

  return 0;
}