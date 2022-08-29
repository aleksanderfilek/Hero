#pragma once

#include"../../Core/Sid.hpp"

#include<vector>

namespace Hero
{

class Actor;

class ActorScene
{
private:
    std::vector<Actor*> actors;

public:
    HERO ActorScene();
    HERO ~ActorScene();

    virtual void Start(){}
    HERO virtual void Update();
    virtual void End(){}

    HERO void AddActor(Actor* actor);
    HERO void RemoveActor(const Sid& Id);
    HERO void ClearActors();
    HERO Actor* GetActor(const Sid& Id);
};

}