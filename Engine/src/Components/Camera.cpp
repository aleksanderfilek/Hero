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

HERO void CameraData::setPerspective(int _width, int _height, float _fov, float _near, float _far)
{
  width = _width;
  height = _height;
  fov = _fov;
  near = _near;
  far = _far;
  projection = projectionMatrix(width, height, fov, near, far);
}

HERO void Camera::dataInit(CameraData* data)
{
  data->transform = (TransformData*)data->actor->GetComponent(SID("Transform"));

  data->view = lookAtMatrix(data->transform->position, data->transform->forward(), Float3::up());
}

HERO void Camera::dataUpdate(CameraData* data)
{
  Float3 target = data->transform->position + data->transform->forward();

  data->view = lookAtMatrix(data->transform->position, target, Float3::up());
}

HERO void Camera::dataDestroy(CameraData* data)
{

}

}