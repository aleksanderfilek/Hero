#include"Menu.hpp"

void Menu::begin()
{
  input = Hero::Core::getSystem<Hero::System::Input>(SID("input"));
  window = Hero::Core::getSystem<Hero::System::Window>(SID("Window"));
  window->setBackgroundColor((Hero::Color){255,0,0,0});

}

void Menu::update()
{
  Hero::System::Window::clear();

  window->render();

  IScene::update();
}

void Menu::close()
{

}