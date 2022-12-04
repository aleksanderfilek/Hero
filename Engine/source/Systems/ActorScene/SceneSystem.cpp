#include"SceneSystem.hpp"
#include"Scene.hpp"

namespace Hero
{

HERO SceneSystem::SceneSystem(const Sid& sid, Scene* StartScene) : ISystem(sid)
{
  NextScene = StartScene;
}

HERO SceneSystem::~SceneSystem()
{

}

HERO void SceneSystem::init()
{
  ISystem::init();
}

HERO void SceneSystem::update()
{    
  if(NextScene != nullptr)
  {
    Scene* previous = CurrentScene;

    CurrentScene = NextScene;
    NextScene = nullptr;
    CurrentScene->Load();
    CurrentScene->Start();

    if(previous != nullptr)
    {
      previous->End();
      delete previous;
    }
  }

  CurrentScene->Update();
}

HERO void SceneSystem::close()
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

HERO void SceneSystem::ChangeScene(Scene* NewScene)
{
  NextScene = NewScene;
}


}
