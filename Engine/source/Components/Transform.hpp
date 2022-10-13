#pragma once

#include"../Systems/ActorScene/Components.hpp"
#include"../Core/Math.hpp"

namespace Hero
{

struct TransformComponent : public Component
{
  Float3 position = Float3::zero();
  Quaternion rotation;
  Float3 scale = Float3::one();

  Matrix4x4 modelMatrix = Matrix4x4::identity();
  bool isDirty = false;
};

HERO void TransformUpdate(TransformComponent& transform);
HERO Float3 TransgormForward(TransformComponent& transform);
HERO Float3 TransgormUp(TransformComponent& transform);
HERO Float3 TransgormRight(TransformComponent& transform);
HERO void TransformRotationSet(TransformComponent& transform, const Quaternion& rotation);
HERO void TransformPositionSet(TransformComponent& transform, const Float3& position);
HERO void TransformScaleSet(TransformComponent& transform, const Float3& scale);

}