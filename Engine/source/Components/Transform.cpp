#include"Transform.hpp"

namespace Hero
{

HERO void TransformUpdate(TransformComponent& transform)
{
  if(!transform.isDirty)
    return;

  transform.modelMatrix  = TRS(transform.position, transform.rotation, transform.scale);
  transform.isDirty = false;
}

HERO Float3 TransformForward(TransformComponent& transform)
{
  Matrix4x4 rotationMatrix = Rotation(transform.rotation);
  Float4 bigForward = rotationMatrix * Float4(0.0f, 0.0f, 1.0f, 0.0f);
  Float3 forward(bigForward);
  forward.normalize();
  return forward;
}

HERO Float3 TransformUp(TransformComponent& transform)
{
  Matrix4x4 rotationMatrix = Rotation(transform.rotation);
  Float4 tup = rotationMatrix * Float4(0.0f, 1.0f, 0.0f, 0.0f);
  Float3 up(tup);
  up.normalize();
  return up;
}

HERO Float3 TransformRight(TransformComponent& transform)
{
  Matrix4x4 rotationMatrix = Rotation(transform.rotation);
  Float4 tright = rotationMatrix * Float4(1.0f, 0.0f, 0.0f, 0.0f);
  Float3 right(tright);
  right.normalize();
  return right;
}

HERO void TransformRotationSet(TransformComponent& transform, const Quaternion& rotation)
{
  transform.rotation = rotation;
  transform.isDirty = true;
}

HERO void TransformPositionSet(TransformComponent& transform, const Float3& position)
{
  transform.position = position;
  transform.isDirty = true;
}

HERO void TransformScaleSet(TransformComponent& transform, const Float3& scale)
{
  transform.scale = scale;
  transform.isDirty = true;
}

}