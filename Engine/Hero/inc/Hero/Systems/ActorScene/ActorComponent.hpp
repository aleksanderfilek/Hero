#pragma once

#include "../../Core/Sid.hpp"

#include <typeinfo>

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

    Sid GetType() { return SID(typeid(*this).name()); }
};

}