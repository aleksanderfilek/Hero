#pragma once 

#include"ISystem.hpp"

#include<vector>

namespace Hero
{
class Actor;
class IComponentSystemHandle;

namespace System
{

class HERO IScene
{
private:
    std::vector<IComponentSystemHandle*> systems;
    std::vector<Actor*> actors;

public:
    HERO IScene();
    HERO ~IScene();

    virtual void begin(){}
    HERO virtual void update();
    virtual void close(){}

    HERO void addSystem(IComponentSystemHandle* system);
    HERO void removeSystem(int index);
    HERO void clearSystems();

    HERO void addActor(Actor* actor);
    HERO void removeActor(int index);
    HERO void clearActors();
};

class HERO Scene : public ISystem
{
private:
    IScene* currentScene = nullptr;
    IScene* nextScene = nullptr;

public:
    HERO Scene(const Sid& sid, IScene* startScene);
    HERO ~Scene();

    HERO void init();
    HERO void update();
    HERO void close();

    HERO void changeScene(IScene* _nextScene);
};
  
}
}