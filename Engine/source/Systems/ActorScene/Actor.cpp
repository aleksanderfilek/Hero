#include "Actor.hpp"
#include "ActorComponent.hpp"
#include "../../Utility/ByteOperations.hpp"
#include "Scene.hpp"

namespace Hero
{

HERO Actor::Actor(const Sid& Name)
 : name(Name)
{
    transform = new Transform();
    AddComponent(transform);
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

HERO void Actor::AddChild(Actor* Child)
{
    for(auto child: children)
    {
        if(child == Child)
        {
            return;
        }
    }

    Child->parent = this;
    children.push_back(Child);
    SceneRef->AddActor(Child);
}

HERO Actor* Actor::GetChild(uint32_t index)
{
    if(index >= children.size())
    {
        return nullptr;
    }

    return children[index];
}

HERO void Actor::AddComponent(ActorComponent* Component)
{
    if(componentsLut.find(Component->GetType()) != componentsLut.end())
    {
        return;
    }
    componentsLut.insert({Component->GetType(), Component});
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
    // size += sizeof(Transform);
    // uint8_t* data = new uint8_t[size];
    // WritePtr(data, &index, (uint8_t*)&transform, sizeof(Transform));
    // bytes = data;
    return size;
}

HERO void Actor::Deserialize(uint8_t* bytes, uint32_t size)
{
    int index = 0;
    //ReadPtr(bytes, &index, (uint8_t*)&transform, size);
}

HERO ICloneable* Actor::Clone()
{
    Actor* actor = new Actor(GetName());
    *actor->GetTransformRef() = *transform;
    return actor;
}

}