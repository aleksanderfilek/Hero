#include"Camera.hpp"
#include "../Systems/ActorScene/Actor.hpp"

namespace Hero
{

HERO Camera::Camera()
{
  MatricesBuffer.Register<Hero::Matrix4x4>(SID("view"));
  MatricesBuffer.Register<Hero::Matrix4x4>(SID("projection"));
  MatricesBuffer.Register<Hero::Matrix4x4>(SID("pixel"));
  MatricesBuffer.Register<Hero::Float3>(SID("viewPos"));
  MatricesBuffer.Apply(0);
}

HERO void Camera::Start()
{
  UpdateProjection();
  UpdateView();
}

HERO void Camera::Update()
{
  UpdateView();
}

HERO void Camera::UpdateProjection()
{
  projection = Hero::projectionMatrix(size.x, size.y, fov, near, far);
  pixel = Hero::pixelScreenMatrix(size.x, size.y, 0.0f, 1.0f);

  MatricesBuffer.Set(SID("projection"), projection);
  MatricesBuffer.Set(SID("pixel"), pixel);
}

HERO void Camera::UpdateView()
{
  Transform transform = GetOwner()->GetTransform();
  Float3 position = transform.GetWorldPosition();

  Float3 target = position + transform.GetWorldRotation().GetForwardVector();
  view = lookAtMatrix(position, target, Float3::up());

  MatricesBuffer.Set(SID("view"), view);
  MatricesBuffer.Set(SID("viewPos"), position);
}

HERO void Camera::SetSize(Int2 Size)
{
  size = Size;
  UpdateProjection();
}

HERO void Camera::SetFov(float FOV)
{
  fov = FOV;
  UpdateProjection();
}

HERO void Camera::SetNearFarPlane(float Near, float Far)
{
  near = Near;
  far = Far;
  UpdateProjection();
}

}