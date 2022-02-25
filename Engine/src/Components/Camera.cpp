#include"Camera.hpp"

#include<iostream>
#include<cmath>

namespace Hero
{

HERO Camera::Camera(int _width, int _height, float _FOV, float _near, float _far)
  : width(_width), height(_height), fov(_FOV), near(_near), far(_far) 
{
  transform = (TransformData*)getComponent<Transform>();

  view = lookAtMatrix(Float3::zero(), Float3::forward(), Float3::up());
  projection = projectionMatrix(width, height, fov, near, far);
}


HERO Camera::~Camera()
{
  
}

HERO void Camera::begin()
{

}

HERO void Camera::update()
{
  Float3 target = transform->position + transform->forward();

  view = lookAtMatrix(transform->position, target, Float3::up());
}
HERO void Camera::close()
{

}

HERO void Camera::setFOV(float _fov)
{
  fov = _fov;
  projection = projectionMatrix(width, height, _fov, near, far);
}

}