#include"Actor.hpp"
#include "ActorComponent.hpp"

namespace Hero
{

HERO Actor::Actor(const Sid& NewId)
 : Id(NewId)
{
  
}

HERO Actor::~Actor()
{
  End();
}

HERO void Actor::Start()
{
    started = true;
    for(ActorComponent* component: components)
    {
        component->Start();
    }
}

HERO void Actor::Update()
{
    for(ActorComponent* component: components)
    {
        component->Update();
    }
}

HERO void Actor::End()
{
    for(ActorComponent* component: components)
    {
        component->End();
    }
}

HERO void Actor::SetPosition(const Float3& Position)
{
    transform.SetPosition(Position);
}

HERO void Actor::SetRotation(const Quaternion& Rotation)
{
    transform.SetRotation(Rotation);
}

HERO void Actor::SetScale(const Float3& Scale)
{
    transform.SetScale(Scale);
}

HERO void Actor::SetTransform(const Transform& Transform)
{
    transform = Transform;
}

HERO void Actor::AddComponent(class ActorComponent* Component)
{
    components.push_back(Component);
    Component->owner = this;
    
    if(started)
    {
        Component->Start();
    }
}

}