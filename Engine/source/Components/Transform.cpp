#include "Transform.hpp"
#include "../Systems/ActorScene/Actor.hpp"

namespace Hero
{

HERO Transform::Transform(Float3 Position, Quaternion Rotation, Float3 Scale)
{
    position = Position;
    rotation = Rotation;
    scale = Scale;
    modelMatrix = TRS(position, rotation, scale);
}

HERO void Transform::SetLocalPosition(Float3 Position)
{
    position = Position;
    isDirty = true;
}

HERO void Transform::SetLocalRotation(Quaternion Rotation)
{
    rotation = Rotation;
    isDirty = true;
}

HERO void Transform::SetLocalScale(Float3 Scale)
{
    scale = Scale;
    isDirty = true;
}

HERO Matrix4x4 Transform::GetLocalModelMatrix()
{
    if(isDirty)
    {
        modelMatrix = TRS(position, rotation, scale);
        isDirty = false;
    }

    return modelMatrix;
}

HERO Float3 Transform::GetWorldPosition()
{
    Matrix4x4 parentMat = Matrix4x4::identity();
    if(GetOwner()->GetParent())
    {
        parentMat = GetOwner()->GetParent()->GetTransformRef()->GetWorldModelMatrix();
    }
    return parentMat * Float4(position);
}

HERO Quaternion Transform::GetWorldRotation()
{
    if(GetOwner()->GetParent())
    {
        return GetOwner()->GetParent()->GetTransformRef()->GetWorldRotation() * rotation;
    }

    return rotation;
}

HERO Float3 Transform::GetWorldScale()
{
    if(GetOwner()->GetParent())
    {
        return GetOwner()->GetParent()->GetTransformRef()->GetWorldScale() * scale;
    }

    return scale;
}

HERO Matrix4x4 Transform::GetWorldModelMatrix()
{
    if(isDirty)
    {
        modelMatrix = TRS(position, rotation, scale);
        isDirty = false;
    }

    if(GetOwner()->GetParent())
    {
        return GetOwner()->GetParent()->GetTransformRef()->GetWorldModelMatrix() * modelMatrix;
    }

    return modelMatrix;
}

HERO Transform& Transform::operator*=(Transform& rhs)
{
    if(isDirty)
    {
        modelMatrix = TRS(position, rotation, scale);
        isDirty = false;
    }

    if(rhs.isDirty)
    {
        rhs.modelMatrix = TRS(rhs.position, rhs.rotation, rhs.scale);
        rhs.isDirty = false;
    }

    Float4 tempPosition = rhs.modelMatrix * Float4(position);
    position = Float3(tempPosition);

    rotation *= rhs.rotation;

    scale.x *= rhs.scale.x;
    scale.y *= rhs.scale.y;
    scale.z *= rhs.scale.z;

    modelMatrix = modelMatrix * rhs.modelMatrix;
}

HERO Transform operator*(Transform& lhs, Transform& rhs)
{
    if(lhs.isDirty)
    {
        lhs.modelMatrix = TRS(lhs.position, lhs.rotation, lhs.scale);
        lhs.isDirty = false;
    }

    if(rhs.isDirty)
    {
        rhs.modelMatrix = TRS(rhs.position, rhs.rotation, rhs.scale);
        rhs.isDirty = false;
    }

    Transform result;
    Float4 tempPosition = lhs.modelMatrix * Float4(rhs.position);
    result.position = Float3(tempPosition);
    result.rotation = lhs.rotation * rhs.rotation;
    result.scale.x = lhs.scale.x * rhs.scale.x;
    result.scale.y = lhs.scale.y * rhs.scale.y;
    result.scale.z = lhs.scale.z * rhs.scale.z;
    result.modelMatrix = TRS(result.position, result.rotation, result.scale);

    return result;
}

}