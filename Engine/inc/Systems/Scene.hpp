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
    IScene();
    ~IScene();

    virtual void begin(){}
    virtual void update();
    virtual void close(){}

    void addSystem(IComponentSystemHandle* system);
    void removeSystem(int index);
    void clearSystems();

    void addActor(Actor* actor);
    void removeActor(int index);
    void clearActors();
};

class HERO Scene : public ISystem
{
private:
    IScene* currentScene = nullptr;
    IScene* nextScene = nullptr;

public:
    Scene(const Sid& sid, IScene* startScene);
    ~Scene();

    void init() override;
    void update() override;
    void close() override;

    void changeScene(IScene* _nextScene);
};
  
}
}