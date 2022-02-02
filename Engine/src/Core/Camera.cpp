#include"Camera.hpp"

#include<iostream>

namespace Hero
{

HERO Camera::Camera()
{
  addComponent<Transform>();
  TransformData* transform = (TransformData*)getComponent<Transform>();
  if(transform == nullptr)
  {
    std::cout<<"null"<<std::endl;
  }
  transform->position = Float3::one();
  removeComponent<Transform>();
}


HERO Camera::~Camera()
{
  
}

HERO void Camera::setPosition(Float3 _position)
{

}

HERO void Camera::setRotation(Float3 _rotation)
{

}

}