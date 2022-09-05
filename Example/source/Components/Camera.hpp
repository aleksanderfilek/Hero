#pragma once

#include"../Hero/Systems/ActorScene/Components.hpp"
#include"../Hero/Core/Math.hpp"

#include"Transform.hpp"
#include"../Utility/UniformBuffer.hpp"

struct CameraComponent : public Hero::Component
{
  UniformBuffer MatricesBuffer;

  Hero::Matrix4x4 view = Hero::Matrix4x4::identity();
  Hero::Matrix4x4 projection = Hero::Matrix4x4::identity();
  Hero::Matrix4x4 pixel = Hero::Matrix4x4::identity();

  int width = 0;
  int height = 0;
  float fov = 0.0f;
  float near = 0.0f;
  float far = 0.0f;
};

void CameraInit(CameraComponent& Camera);
void CameraProjectionSet(CameraComponent& Camera);
void CameraViewSet(CameraComponent& Camera, TransformComponent& transform);