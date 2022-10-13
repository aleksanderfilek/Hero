#pragma once

#include"../../Core/Sid.hpp"

#include<vector>

namespace Hero
{

class Actor
{
private:    
    Sid Id;

protected:
    class ActorScene* SceneRef = nullptr;

public:
    HERO Actor(const Sid& NewId);
    HERO ~Actor();

    virtual void Start(){}
    virtual void Update(){}
    virtual void End(){}

    inline Sid GetId(){ return Id; }

    friend class ActorScene;
};

} 
