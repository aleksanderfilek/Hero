#pragma once

#include"../Systems/ActorScene/ActorComponent.hpp"
#include"../Core/Math.hpp"

namespace Hero
{

class Transform : public ActorComponent
{
private:
    Float3 position = Float3::zero();
    Quaternion rotation;
    Float3 scale = Float3::one();

    bool isDirty = false;
    Matrix4x4 modelMatrix = Matrix4x4::identity();
    
public:

    Transform(){};
    HERO Transform(Float3 Position, Quaternion Rotation, Float3 Scale);

    Float3 GetLocalPosition() const { return position; }
    Quaternion GetLocalRotation() const { return rotation; }
    Float3 GetLocalScale() const { return scale; }
    HERO Matrix4x4 GetLocalModelMatrix();
    HERO void SetLocalPosition(Float3 Position);
    HERO void SetLocalRotation(Quaternion Rotation);
    HERO void SetLocalScale(Float3 Scale);

    HERO Float3 GetWorldPosition();
    HERO Quaternion GetWorldRotation();
    HERO Float3 GetWorldScale();
    HERO Matrix4x4 GetWorldModelMatrix();

    HERO Transform& operator*=(Transform& rhs);

    friend Transform operator*(Transform& lhs, Transform& rhs);
};

HERO Transform operator*(Transform& lhs, Transform& rhs);

}