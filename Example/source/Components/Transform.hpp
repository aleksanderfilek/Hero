#pragma once

#include"../Hero/Systems/ActorScene/Components.hpp"
#include"../Hero/Core/Math.hpp"

struct TransformComponent : public Hero::Component
{
  Hero::Float3 position = Hero::Float3::zero();
  Hero::Float3 rotation = Hero::Float3::zero();
  Hero::Float3 scale = Hero::Float3::one();

  Hero::Matrix4x4 modelMatrix = Hero::Matrix4x4::identity();
  bool isDirty = false;
};

void TransformUpdate(TransformComponent& transform);
Hero::Float3 TransgormForward(TransformComponent& transform);
Hero::Float3 TransgormUp(TransformComponent& transform);
Hero::Float3 TransgormRight(TransformComponent& transform);
void TransformRotationSet(TransformComponent& transform, const Hero::Float3& rotation);
void TransformPositionSet(TransformComponent& transform, const Hero::Float3& position);