#pragma once 

#include"../../Core/ISystem.hpp"
#include"../../Core/Sid.hpp"

namespace Hero
{

class ActorScene;

class ActorSceneSystem : public ISystem
{
private:
    ActorScene* CurrentScene = nullptr;
    ActorScene* NextScene = nullptr;

public:
    HERO ActorSceneSystem(const Sid& sid, ActorScene* StartScene);
    HERO ~ActorSceneSystem();

    HERO void init();
    HERO void update();
    HERO void close();

    HERO void ChangeScene(ActorScene* NewScene);
};

}