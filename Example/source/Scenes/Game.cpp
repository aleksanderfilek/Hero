#include"Game.hpp"

#include"../Hero/Core/Core.hpp"
#include"../Actors/Player.hpp"
#include"../Actors/Cubemap.hpp"
#include"../Actors/Terrain.hpp"
#include"../Actors/DirectionalSun.hpp"
#include"../Physics/PhysicsManager.hpp"

void Game::Start()
{
  ActorScene::Start();

  window = Hero::Core::getSystem<Hero::System::Window>(SID("Window"));
  window->setBackgroundColor((Hero::Color){0,0,0,255});
  window->setDepthTest(true);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT); 

  AddActor(new PhysicsManager(SID("PhysicsManager")));
  AddActor(new Cubemap(SID("Cubemap")));
  AddActor(new Player(SID("Player")));
  AddActor(new Terrain(SID("Terrain")));
  AddActor(new DirectionalSun(SID("Sun")));
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