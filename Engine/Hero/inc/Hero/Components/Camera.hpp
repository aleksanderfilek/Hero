#pragma once

#include"../Systems/ActorScene/Components.hpp"
#include"../Core/Math.hpp"
#include"Transform.hpp"
#include"../Graphics/UniformBlock.hpp"

namespace Hero
{

struct CameraComponent : public Component
{
  UniformBlock MatricesBuffer;

  Matrix4x4 view = Matrix4x4::identity();
  Matrix4x4 projection = Matrix4x4::identity();
  Matrix4x4 pixel = Matrix4x4::identity();

  int width = 0;
  int height = 0;
  float fov = 0.0f;
  float near = 0.0f;
  float far = 0.0f;
};

HERO void CameraInit(CameraComponent& Camera);
HERO void CameraProjectionSet(CameraComponent& Camera);
HERO void CameraViewSet(CameraComponent& Camera, TransformComponent& transform);

}