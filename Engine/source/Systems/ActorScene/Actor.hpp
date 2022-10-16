#pragma once

#include "../../Core/Sid.hpp"
#include "../../Core/Math.hpp"
#include "ISerializable.hpp"
#include "ICloneable.hpp"

#include <vector>
#include <typeinfo>

namespace Hero
{

class Actor : public ISerializable, public ICloneable
{
    friend class Scene;

private:    
    Sid name;

    Transform transform;
    std::vector<class ActorComponent*> components;
    class Scene* SceneRef = nullptr;

    bool started = false;

public:
    HERO Actor(const Sid& Name);
    HERO ~Actor();

    HERO virtual void Start();
    HERO virtual void Update();
    HERO virtual void End();

    inline Sid GetName(){ return name; }
    inline uint32_t GetId(){ return name.id; }
    inline Sid GetType(){ return SID(typeid(*this).name()); };

    HERO void SetPosition(const Float3& Position);
    HERO void SetRotation(const Quaternion& Rotation);
    HERO void SetScale(const Float3& Scale);
    HERO void SetTransform(const Transform& Transform);

    Float3 GetPosition() const { return transform.GetPosition(); }
    Quaternion GetRotation() const { return transform.GetRotation(); }
    Float3 GetScale() const { return transform.GetScale(); }
    Transform GetTransform() const { return transform; }
    Transform* GetTransformRef() { return &transform; }
    
    class Scene* GetScene(){ return SceneRef; }

    HERO void AddComponent(class ActorComponent* Component);

    HERO virtual uint32_t Serialize(uint8_t*& bytes) override;
    HERO virtual void Deserialize(uint8_t* bytes, uint32_t size) override;
    HERO virtual Actor* Clone() override;

};

} 
