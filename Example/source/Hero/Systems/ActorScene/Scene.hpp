#pragma once

#include "../../Core/Sid.hpp"
#include "../../Core/Math.hpp"
#include "Reflection.hpp"
#include "Actor.hpp"

#include<vector>

namespace Hero
{

class Scene
{
private:
    std::vector<Actor*> actors;
    Reflection reflection;

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

    template<class T> void AddReflection()
    {
        reflection.Add<T>();
    }

    template<class T> Actor* Spawn(const Sid& Name, Transform transform = Transform())
    {
        Actor* actor = reflection.Spawn(GetType<T>());
        actor->SetName(Name);
        actor->SetTransform(transform);
        return actor;
    }
};

}