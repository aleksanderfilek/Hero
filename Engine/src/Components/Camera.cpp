#include"Camera.hpp"

#include<iostream>

namespace Hero
{

HERO Camera::Camera(int width, int height, float FOV, float near, float far)
{
  transform = (TransformData*)addComponent<Transform>();

  view = lookAtMatrix(Float3::zero(), Float3::forward(), Float3::up());
  projection = projectionMatrix(width, height, FOV, near, far);
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
  Matrix4x4 rotationMatrix = Mat4x4Identity;
  rotateXYZM4x4(&rotationMatrix, transform->rotation);
  Float4 forward = multiplyM4x4F4(rotationMatrix, {0.0f, 0.0f, 1.0f, 0.0f});
  Float3 target = addF3(transform->position, {forward.x, forward.y, forward.z});
  view = lookAtMatrix(transform->position, target, Float3::up());
}

void Camera::close()
{

}

}