#include"Scene.hpp"
#include"../Components/ComponentContext.hpp"
#include"../Components/Actor.hpp"
#include"../Components/Transform.hpp"

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
  //clearContexts();
  clearActors();
}

HERO void IScene::update()
{
  for(auto system: systemsContext)
  {
    system.second->Update();
  }
}

HERO void IScene::addContext(const Sid& sid, ComponentContext* context)
{
  if(systemsContext.find(sid) != systemsContext.end())
  {
    #ifdef HERO_DEBUG
    std::cout<<"[IScene] - ComponentSystem with sid: "<<sid<<" aleardy exists in the scene."<<std::endl;
    #endif
    return;
  }

  bool result = systemsContext.insert({sid, context}).second;
  if(!result)
  {
    #ifdef HERO_DEBUG
    std::cout<<"[IScene] - Could not add system with sid: "<<sid<<" to the scene."<<std::endl;
    #endif
  }
}

HERO void IScene::removeContext(const Sid& sid)
{
  if(systemsContext.find(sid) == systemsContext.end())
  {
    #ifdef HERO_DEBUG
    std::cout<<"[IScene] - ComponentSystem with sid: "<<sid<<" aleardy exists in the scene."<<std::endl;
    #endif
    return;
  }

  systemsContext.erase(sid);
}

HERO ComponentContext* IScene::getContext(const Sid& sid)
{
  auto context = systemsContext.find(sid);
  if(context == systemsContext.end())
  {
    #ifdef HERO_DEBUG
    std::cout<<"[IScene] - ComponentSystem with sid: "<<sid<<" aleardy exists in the scene."<<std::endl;
    #endif
    return nullptr;
  }

  return context->second;
}

HERO void IScene::clearContexts()
{
  for(auto context: systemsContext)
  {
    delete context.second;
  }
}

HERO void IScene::addActor(Actor* actor)
{
  actors.push_back(actor);

  TransformData* data = (TransformData*)actor->GetComponent(SID("Transform"));
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
    delete actor;
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
    delete actor;
  }
  actors.clear();
}

HERO void IScene::load(const std::string& path)
{

}

HERO void IScene::save(const std::string& path)
{

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