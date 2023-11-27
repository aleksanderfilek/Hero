#pragma once

#include"../Systems/ActorScene/ActorComponent.hpp"
#include"../Core/Math.hpp"
#include"../Graphics/UniformBlock.hpp"

namespace Hero
{

class Camera : public ActorComponent
{
private:
  UniformBlock MatricesBuffer;

  Matrix4x4 view = Matrix4x4::identity();
  Matrix4x4 projection = Matrix4x4::identity();
  Matrix4x4 pixel = Matrix4x4::identity();

  Int2 size = {0, 0};
  float fov = 0.0f;
  float near = 0.0f;
  float far = 0.0f;

  HERO void UpdateProjection();
  HERO void UpdateView();

public:
  HERO Camera();

  HERO void Start() override;
  HERO void Update() override;

  HERO void SetSize(Int2 Size);
  HERO void SetFov(float FOV);
  HERO void SetNearFarPlane(float Near, float Far);
};

}