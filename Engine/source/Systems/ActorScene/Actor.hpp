#pragma once

#include "../../Core/Sid.hpp"
#include "../../Core/Math.hpp"
#include "ISerializable.hpp"
#include "ICloneable.hpp"
#include "../../Components/Transform.hpp"

#include <vector>
#include <unordered_map>
#include <typeinfo>

namespace Hero
{

template<class T>
Sid GetType()
{ 
    return SID(typeid(T).name()); 
};

class Actor : public ISerializable, public ICloneable
{
    friend class Scene;

private:    
    Sid name;

    std::vector<class ActorComponent*> components;
    std::unordered_map<Sid, class ActorComponent*, SidHashFunction> componentsLut;
    class Transform* transform;

    class Scene* SceneRef = nullptr;

    Actor* parent = nullptr;
    std::vector<Actor*> children;

    bool started = false;

public:
    HERO Actor(const Sid& Name);

    HERO void Destroy();

    HERO virtual void Start();
    HERO virtual void Update();
    HERO virtual void End();

    inline Sid GetName(){ return name; }
    void SetName(const Sid& Name){ name = Name; }
    inline uint32_t GetId(){ return name.id; }
    Sid GetType() { return SID(typeid(*this).name()); }

    Transform GetTransform() const { return *transform; }
    Transform* GetTransformRef() { return transform; }
    
    class Scene* GetScene(){ return SceneRef; }
    Actor* GetParent(){ return parent; }

    HERO void AddChild(Actor* Child);
    HERO Actor* GetChild(uint32_t index);

    HERO void AddComponent(class ActorComponent* Component);

    HERO virtual uint32_t Serialize(uint8_t*& bytes) override;
    HERO virtual void Deserialize(uint8_t* bytes, uint32_t size) override;
    HERO virtual Actor* Clone() override;

};

} 
