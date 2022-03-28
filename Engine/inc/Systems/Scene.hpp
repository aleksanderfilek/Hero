#pragma once 

#include"ISystem.hpp"
#include"Sid.hpp"

#include<string>
#include<vector>
#include<unordered_map>

namespace Hero
{
class Actor;
class ComponentContext;

namespace System
{

class HERO IScene
{
private:
    std::unordered_map<Sid, ComponentContext*, SidHashFunction> systemsContext;
    std::vector<Actor*> actors;

public:
    HERO IScene();
    HERO ~IScene();

    virtual void begin(){}
    HERO virtual void update();
    virtual void close(){}

    HERO void addContext(const Sid& sid, ComponentContext* context);
    HERO void removeContext(const Sid& sid);
    HERO ComponentContext* getContext(const Sid& sid);
    HERO void clearContexts();

    HERO void addActor(Actor* actor);
    HERO void removeActor(int index);
    HERO void clearActors();

    HERO void load(const std::string& path);
    HERO void save(const std::string& path);
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