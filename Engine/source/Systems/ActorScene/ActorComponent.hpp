#pragma once

namespace Hero
{

class ActorComponent
{
    friend class Actor;

private:
    class Actor* owner = nullptr;

public:
    virtual void Start(){}
    virtual void Update(){}
    virtual void End(){}

    class Actor* GetOwner() const { return owner; }
};

}