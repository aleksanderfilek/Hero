#include"Game.hpp"

#include"../Hero/Core/Core.hpp"
#include"../Actors/Player.hpp"
#include"../Actors/Cubemap.hpp"

void Game::Start()
{
  ActorScene::Start();

  window = Hero::Core::getSystem<Hero::System::Window>(SID("Window"));
  window->setBackgroundColor((Hero::Color){0,0,0,255});

  AddActor(new Cubemap(SID("Cubemap")));
  AddActor(new Player(SID("Player")));
}

void Game::Update()
{
  Hero::System::Window::clear();

  ActorScene::Update();

  window->render();
}

void Game::End()
{
  ActorScene::End();
}