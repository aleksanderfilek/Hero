#include "Actor.hpp"
#include "ActorComponent.hpp"
#include "../../Utility/ByteOperations.hpp"
#include "Scene.hpp"

namespace Hero
{

HERO Actor::Actor(const Sid& Name)
 : name(Name)
{
  
}

HERO void Actor::Destroy()
{
    SceneRef->RemoveActor(GetName());
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

HERO uint32_t Actor::Serialize(uint8_t*& bytes)
{
    int index = 0;
    uint32_t size = 0;
    size += sizeof(Transform);
    uint8_t* data = new uint8_t[size];
    WritePtr(data, &index, (uint8_t*)&transform, sizeof(Transform));
    bytes = data;
    return size;
}

HERO void Actor::Deserialize(uint8_t* bytes, uint32_t size)
{
    int index = 0;
    ReadPtr(bytes, &index, (uint8_t*)&transform, size);
}

HERO Actor* Actor::Clone()
{
    Actor* actor = new Actor(GetName());
    actor->SetTransform(actor->GetTransform());
    return actor;
}

}