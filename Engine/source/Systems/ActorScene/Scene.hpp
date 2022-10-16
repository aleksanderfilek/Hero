#pragma once

#include"../../Core/Sid.hpp"
#include "../../Core/Math.hpp"

#include<vector>

namespace Hero
{

class Actor;

class Scene
{
private:
    std::vector<Actor*> actors;

public:
    HERO Scene();
    HERO ~Scene();

    virtual void Start(){}
    HERO virtual void Update();
    virtual void End(){}

    HERO void AddActor(Actor* actor);
    HERO void RemoveActor(const Sid& Name);
    HERO void ClearActors();
    HERO Actor* GetActor(const Sid& Name);
    HERO Actor* GetActor(uint32_t Id);

    HERO Actor* GetActorUnderCursor(Int2 MousePosition);
};

}