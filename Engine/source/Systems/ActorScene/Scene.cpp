#include"Scene.hpp"
#include"Actor.hpp"

#include<fstream>

namespace Hero
{

HERO Scene::Scene()
{
  
}

HERO Scene::~Scene()
{
  ClearActors();
}

HERO void Scene::Update()
{
  for(Actor* actor: actors)
  {
    actor->Update();
  }
}

HERO void Scene::AddActor(Actor* actor)
{
  actor->SceneRef = this;
  actor->Start();
  actors.push_back(actor);
}

HERO void Scene::RemoveActor(const Sid& Id)
{
  int index = -1;
  for(index = 0; index < actors.size(); index++)
  {
    if(actors[index]->GetId() == Id)
    {
        break;
    }
  }

  if(index >= actors.size())
  {
    return;
  }

  Actor* actor = actors[index];
  delete actor;
  actors.erase(actors.begin() + index);
}

HERO void Scene::ClearActors()
{
  for(Actor* actor: actors)
  {
    delete actor;
  }
  actors.clear();
}

HERO Actor* Scene::GetActor(const Sid& Id)
{
  int index = -1;
  for(index = 0; index < actors.size(); index++)
  {
    if(actors[index]->GetId() == Id)
    {
        break;
    }
  }

  if(index >= actors.size())
  {
    return nullptr;
  }

  return actors[index];
}

}