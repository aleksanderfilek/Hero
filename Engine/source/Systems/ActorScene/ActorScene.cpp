#include"ActorScene.hpp"
#include"Actor.hpp"

#include<fstream>

namespace Hero
{

HERO ActorScene::ActorScene()
{
  
}

HERO ActorScene::~ActorScene()
{
  ClearActors();
}

HERO void ActorScene::Update()
{
  for(Actor* actor: actors)
  {
    actor->Update();
  }
}

HERO void ActorScene::AddActor(Actor* actor)
{
  actor->SceneRef = this;
  actor->Start();
  actors.push_back(actor);
}

HERO void ActorScene::RemoveActor(const Sid& Id)
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

HERO void ActorScene::ClearActors()
{
  for(Actor* actor: actors)
  {
    actor->End();
    delete actor;
  }
  actors.clear();
}

HERO Actor* ActorScene::GetActor(const Sid& Id)
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