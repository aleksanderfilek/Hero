#include"ActorSceneSystem.hpp"
#include"ActorScene.hpp"

namespace Hero
{

HERO ActorSceneSystem::ActorSceneSystem(const Sid& sid, ActorScene* StartScene) : ISystem(sid)
{
  NextScene = StartScene;
}

HERO ActorSceneSystem::~ActorSceneSystem()
{

}

HERO void ActorSceneSystem::init()
{
  ISystem::init();
}

HERO void ActorSceneSystem::update()
{    
  if(NextScene != nullptr)
  {
    if(CurrentScene != nullptr)
    {
      CurrentScene->End();
      delete CurrentScene;
    }
    CurrentScene = NextScene;
    NextScene = nullptr;
    
    CurrentScene->Start();

  }

  CurrentScene->Update();
}

HERO void ActorSceneSystem::close()
{
  ISystem::close();

  if(NextScene != nullptr)
  {
    delete NextScene;
  }

  if(CurrentScene != nullptr)
  {
    CurrentScene->End();
    delete CurrentScene;
  }
}

HERO void ActorSceneSystem::ChangeScene(ActorScene* NewScene)
{
  NextScene = NewScene;
}


}
