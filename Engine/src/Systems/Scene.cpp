#include"Scene.hpp"
#include"IComponent.hpp"
#include"Actor.hpp"
#include"Components/Transform.hpp"

#include<iostream>

namespace Hero
{
namespace System
{

HERO IScene::IScene()
{
  
}

HERO IScene::~IScene()
{
  clearSystems();
  clearActors();
}

HERO void IScene::update()
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

HERO void IScene::addSystem(IComponentSystemHandle* system)
{
  systems.push_back(system);
}

HERO void IScene::removeSystem(int index)
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

HERO void IScene::clearSystems()
{
  systems.clear();
}

HERO void IScene::addActor(Actor* actor)
{
  actor->begin();
  actors.push_back(actor);

  TransformData* data = (TransformData*)actor->getComponent<Transform>();
  for(auto child: data->getChildren())
  {
    addActor(child->actor);
  }
}

HERO void IScene::removeActor(int index)
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

HERO void IScene::clearActors()
{
  for(auto actor: actors)
  {
    actor->close();
  }
  actors.clear();
}

HERO Scene::Scene(const Sid& sid, IScene* startScene) : ISystem(sid)
{
  nextScene = startScene;
}

HERO Scene::~Scene()
{

}

HERO void Scene::init()
{
  ISystem::init();
}

HERO void Scene::update()
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

  currentScene->update();
}

HERO void Scene::close()
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

HERO void Scene::changeScene(IScene* _nextScene)
{
  nextScene = _nextScene;
}


}
}