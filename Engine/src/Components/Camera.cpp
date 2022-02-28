#include"Camera.hpp"
#include"Actor.hpp"

#include<iostream>
#include<cmath>

namespace Hero
{

HERO void CameraData::setFOV(float _fov)
{
  fov = _fov;
  projection = projectionMatrix(width, height, _fov, near, far);
}

HERO void CameraData::setPerspective(int _width, int _height, float _FOV, float _near, float _far)
{
  projection = projectionMatrix(width, height, fov, near, far);
}

void Camera::dataInit(CameraData* data)
{
  data->transform = (TransformData*)data->actor->getComponent<Transform>();

  data->view = lookAtMatrix(data->transform->position, data->transform->forward(), Float3::up());
}

void Camera::dataUpdate(CameraData* data)
{
  Float3 target = data->transform->position + data->transform->forward();

  data->view = lookAtMatrix(data->transform->position, target, Float3::up());
}

void Camera::dataDestroy(CameraData* data)
{

}

}