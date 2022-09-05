#include"Camera.hpp"

void CameraInit(CameraComponent& Camera)
{
  Camera.MatricesBuffer.Register<Hero::Matrix4x4>(SID("view"));
  Camera.MatricesBuffer.Register<Hero::Matrix4x4>(SID("projection"));
  Camera.MatricesBuffer.Register<Hero::Matrix4x4>(SID("pixel"));
  Camera.MatricesBuffer.Apply(0);
}

void CameraProjectionSet(CameraComponent& Camera)
{
  Camera.projection = Hero::projectionMatrix(Camera.width, Camera.height, Camera.fov, Camera.near, Camera.far);

  Camera.pixel = Hero::pixelScreenMatrix(Camera.width, Camera.height, 0.0f, 1.0f);

  Camera.MatricesBuffer.Set(SID("projection"), Camera.projection);
  Camera.MatricesBuffer.Set(SID("pixel"), Camera.pixel);
}

void CameraViewSet(CameraComponent& Camera, TransformComponent& transform)
{
  Hero::Float3 target = transform.position + TransgormForward(transform);
  Camera.view = Hero::lookAtMatrix(transform.position, target, Hero::Float3::up());

  Camera.MatricesBuffer.Set(SID("view"), Camera.view);
}