#include"Scene.hpp"
#include"IComponent.hpp"
#include"Actor.hpp"

#include<iostream>

namespace Hero
{
namespace System
{

IScene::IScene()
{
  
}

IScene::~IScene()
{
  clearSystems();
  clearActors();
}

void IScene::update()
{
  for(auto system: systems)
  {
    system->update();
  }

  for(auto actor: actors)
  {
    actor->update();
  }
}

void IScene::addSystem(IComponentSystemHandle* system)
{
  systems.push_back(system);
}

void IScene::removeSystem(int index)
{
  try 
  {
    IComponentSystemHandle* system = systems.at(index);
    systems.erase(systems.begin() + index);
  }
  catch (std::out_of_range const& exc) 
  {
    std::cout<<exc.what()<<std::endl;
  }
}

void IScene::clearSystems()
{
  systems.clear();
}

void IScene::addActor(Actor* actor)
{
  actor->begin();
  actors.push_back(actor);
}

void IScene::removeActor(int index)
{
  try 
  {
    Actor* actor = actors.at(index);
    actor->close();
    actors.erase(actors.begin() + index);
  }
  catch (std::out_of_range const& exc) 
  {
    std::cout<<exc.what()<<std::endl;
  }
}

void IScene::clearActors()
{
  for(auto actor: actors)
  {
    actor->close();
  }
  actors.clear();
}

Scene::Scene(const Sid& sid, IScene* startScene) : ISystem(sid)
{
  nextScene = startScene;
}

Scene::~Scene()
{

}

void Scene::init()
{
  ISystem::init();
}

void Scene::update()
{
  if(nextScene != nullptr)
  {
    if(currentScene != nullptr)
    {
      currentScene->close();
      delete currentScene;
    }
    currentScene = nextScene;
    nextScene = nullptr;
    currentScene->begin();
  }
}

void Scene::close()
{
  ISystem::close();

  if(nextScene != nullptr)
  {
    delete nextScene;
  }

  if(currentScene != nullptr)
  {
    currentScene->close();
    delete currentScene;
  }
}


}
}