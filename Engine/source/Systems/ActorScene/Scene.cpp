#include"Scene.hpp"
#include"Actor.hpp"
#include"../../Actors/Systems/ForwardRenderer.hpp"

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
  if(actorsToRemove.size() > 0)
  {
    for(int actorId: actorsToRemove)
    {
      Actor* actor = actors[actorId];
      actor->End();
      delete actor;
      actors.erase(actors.begin() + actorId);
    }
    actorsToRemove.clear();
  }

  for(Actor* actor: actors)
  {
    actor->Update();
  }
}

HERO void Scene::AddActor(Actor* actor)
{
  actor->SceneRef = this;
  actors.push_back(actor);
  actor->Start();
}

HERO void Scene::RemoveActor(const Sid& Name)
{
  int index = -1;
  for(index = 0; index < actors.size(); index++)
  {
    if(actors[index]->GetName() == Name)
    {
        break;
    }
  }

  if(index >= actors.size())
  {
    return;
  }

  actorsToRemove.push_back(index);
}

HERO void Scene::RemoveActor(Actor* actor)
{
  int index = -1;
  for(index = 0; index < actors.size(); index++)
  {
    if(actors[index] == actor)
    {
        break;
    }
  }

  if(index >= actors.size())
  {
    return;
  }

  actorsToRemove.push_back(index);
}

HERO void Scene::ClearActors()
{
  for(int i = actors.size() - 1; i >= 0; i--)
  {
    actors[i]->End();
    delete actors[i];
  }
  actors.clear();
}

HERO Actor* Scene::GetActor(const Sid& Name)
{
  int index = -1;
  for(index = 0; index < actors.size(); index++)
  {
    if(actors[index]->GetName() == Name)
    {
      return actors[index];
    }
  }

  return nullptr;
}

HERO Actor* Scene::GetActor(uint32_t Id)
{
  int index = -1;
  for(index = 0; index < actors.size(); index++)
  {
    if((actors[index]->GetId() & 0x00FFFFFF) == (Id&0x00FFFFFF))//hack
    {
      return actors[index];
    }
  }

  return nullptr;
}

HERO Actor* Scene::GetActorUnderCursor(Int2 MousePosition)
{
  ForwardRenderer* renderer = (ForwardRenderer*)GetActor(SID("Renderer"));
  uint32_t id = renderer->GetIdOnPosition(MousePosition);
  return GetActor(id);
}

}