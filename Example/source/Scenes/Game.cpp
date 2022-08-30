#include"Game.hpp"

#include"../Hero/Core/Core.hpp"
#include"../Actors/Player.hpp"

void Game::Start()
{
  ActorScene::Start();

  input = Hero::Core::getSystem<Hero::System::Input>(SID("input"));
  window = Hero::Core::getSystem<Hero::System::Window>(SID("Window"));
  window->setBackgroundColor((Hero::Color){0,0,0,255});

  AddActor(new Player(SID("Player")));
}

void Game::Update()
{
  ActorScene::Update();

  Hero::System::Window::clear();

  window->render();
}

void Game::End()
{
  ActorScene::End();
}