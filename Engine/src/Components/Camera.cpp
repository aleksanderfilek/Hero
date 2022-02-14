#include"Camera.hpp"

#include<iostream>

namespace Hero
{

HERO Camera::Camera(int _width, int _height, float _FOV, float _near, float _far)
  : width(_width), height(_height), fov(_FOV), near(_near), far(_far)
{
  transform = (TransformData*)addComponent<Transform>();

  view = lookAtMatrix(Float3::zero(), Float3::forward(), Float3::up());
  projection = projectionMatrix(width, height, fov, near, far);
  invProjection = invertM4x4(projection);
}


HERO Camera::~Camera()
{
  
}

void Camera::begin()
{

}

void Camera::update()
{
  Matrix4x4 rotationMatrix = Matrix4x4::identity();
  rotateXYZM4x4(&rotationMatrix, transform->rotation);
  Float4 forward = multiplyM4x4F4(rotationMatrix, {0.0f, 0.0f, 1.0f, 0.0f});
  Float3 target = addF3(transform->position, {forward.x, forward.y, forward.z});
  view = lookAtMatrix(transform->position, target, Float3::up());
}

void Camera::close()
{

}

HERO void Camera::setFOV(float _fov)
{
  fov = _fov;
  projection = projectionMatrix(width, height, _fov, near, far);
  invProjection = invertM4x4(projection);
}

}