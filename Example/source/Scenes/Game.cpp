#include"Game.hpp"

#include"../Hero/Core/Core.hpp"

void Game::Start()
{
  input = Hero::Core::getSystem<Hero::System::Input>(SID("input"));
  window = Hero::Core::getSystem<Hero::System::Window>(SID("Window"));
  window->setBackgroundColor((Hero::Color){0,0,0,255});

}

void Game::Update()
{
  Hero::System::Window::clear();

  window->render();
}

void Game::End()
{

}