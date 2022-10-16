#pragma once

#include "../../Core/Sid.hpp"
#include "../../Core/Math.hpp"

#include<vector>

namespace Hero
{

class Actor
{
    friend class Scene;

private:    
    Sid name;

    Transform transform;
    std::vector<class ActorComponent*> components;
    class Scene* SceneRef = nullptr;
    Actor* parent = nullptr;

    bool started = false;

public:
    HERO Actor(const Sid& Name);
    HERO ~Actor();

    HERO virtual void Start();
    HERO virtual void Update();
    HERO virtual void End();

    inline Sid GetName(){ return name; }
    inline uint32_t GetId(){ return name.id; }

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

};

} 
