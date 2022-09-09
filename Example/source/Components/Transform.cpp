#include"Transform.hpp"

void TransformUpdate(TransformComponent& transform)
{
  if(!transform.isDirty)
    return;

  transform.modelMatrix  = Hero::TRS(transform.position, transform.rotation, transform.scale);
  transform.isDirty = true;
}

Hero::Float3 TransgormForward(TransformComponent& transform)
{
  Hero::Matrix4x4 rotationMatrix = Hero::Matrix4x4::identity();
  Hero::rotateXYZ(rotationMatrix, transform.rotation);
  Hero::Float4 bigForward = rotationMatrix * Hero::Float4(0.0f, 0.0f, 1.0f, 0.0f);
  Hero::Float3 forward(bigForward);
  forward.normalize();
  return forward;
}

Hero::Float3 TransgormUp(TransformComponent& transform)
{
  Hero::Matrix4x4 rotationMatrix = Hero::Matrix4x4::identity();
  Hero::rotateXYZ(rotationMatrix, transform.rotation);
  Hero::Float4 tup = rotationMatrix * Hero::Float4(0.0f, 1.0f, 0.0f, 0.0f);
  Hero::Float3 up(tup);
  up.normalize();
  return up;
}

Hero::Float3 TransgormRight(TransformComponent& transform)
{
  Hero::Matrix4x4 rotationMatrix = Hero::Matrix4x4::identity();
  Hero::rotateXYZ(rotationMatrix, transform.rotation);
  Hero::Float4 tright = rotationMatrix * Hero::Float4(1.0f, 0.0f, 0.0f, 0.0f);
  Hero::Float3 right(tright);
  right.normalize();
  return right;
}

void TransformRotationSet(TransformComponent& transform, const Hero::Float3& rotation)
{
  transform.rotation = rotation;
  transform.isDirty = true;
}

void TransformPositionSet(TransformComponent& transform, const Hero::Float3& position)
{
  transform.position = position;
  transform.isDirty = true;
}

void TransformScaleSet(TransformComponent& transform, const Hero::Float3& scale)
{
  transform.scale = scale;
  transform.isDirty = true;
}