#include"Player.hpp"

#include"Core/Core.hpp"
#include"Core/Math.hpp"
#include"Core/Time.hpp"
#include"Systems/Window.hpp"
#include"ThirdParty.hpp"
#include<iostream>
#include"cmath"
#include"Components/Transform.hpp"
#include"Pistol.hpp"

#define SPEED 10.0f

Player::Player(int _width, int _height, float _FOV, float _near, float _far)
:Camera( _width,  _height,  _FOV,  _near,  _far)
{
  input = Hero::Core::getSystem<Hero::System::Input>(SID("input"));

  Hero::TransformData* data = (Hero::TransformData*)getComponent<Hero::Transform>();
  // Pistol* pistol = new Pistol();
  // std::cout<<"Pl "<<data->index<<std::endl;
  // //Hero::TransformData* data2 = (Hero::TransformData*)pistol->getComponent<Hero::Transform>();
  // //std::cout<<"Pis "<<data2->index<<std::endl;

  // // // data->setPosition({0.0f, 0.0f, 5.0f});
  // // // data->setScale({0.5f, 0.5f, 0.5f});
  // //data->addChild(data2);
  // delete pistol;
}

void Player::begin()
{

}

void Player::keyboard()
{
  float deltaTime = Hero::Time::getDeltaTime();
  Hero::Float3 forward = transform->forward();
  Hero::Float3 right = transform->right();
  Hero::Float3 up = transform->up();

  Hero::Float3 deltaPosition = Hero::Float3::zero();
  if(input->keyPressed(Hero::System::Input::KeyCode::W))
  {
    deltaPosition = Hero::addF3(deltaPosition, Hero::multiplyF3(forward, SPEED));
  }
  else if(input->keyPressed(Hero::System::Input::KeyCode::S))
  {
    deltaPosition = Hero::addF3(deltaPosition, Hero::multiplyF3(forward, -SPEED));
  }
  if(input->keyPressed(Hero::System::Input::KeyCode::D))
  {
    deltaPosition = Hero::addF3(deltaPosition, Hero::multiplyF3(right, SPEED));
  }
  else if(input->keyPressed(Hero::System::Input::KeyCode::A))
  {
    deltaPosition = Hero::addF3(deltaPosition, Hero::multiplyF3(right, -SPEED));
  }
  if(input->keyPressed(Hero::System::Input::KeyCode::SPACE))
  {
    deltaPosition = Hero::addF3(deltaPosition, Hero::multiplyF3(up, SPEED));
  }
  else if(input->keyPressed(Hero::System::Input::KeyCode::LCTRL))
  {
    deltaPosition = Hero::addF3(deltaPosition, Hero::multiplyF3(up, -SPEED));
  }

  transform->setPosition(Hero::addF3(transform->position, Hero::multiplyF3(deltaPosition, deltaTime)));
}

void Player::mouse()
{
  int x=0, y=0;
  SDL_GetRelativeMouseState(&x, &y);
  //input->getMousePosition(&x, &y);

  float xpos = (float)x;
  float ypos = (float)y;

  float xoffset = xpos/320.0f;
  float yoffset = ypos/240.0f; // reversed since y-coordinates go from bottom to top

  float sensitivity = 10.0f; // change this value to your liking
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw += xoffset;
  pitch += yoffset;

  // make sure that when pitch is out of bounds, screen doesn't get flipped
  if (pitch > 89.0f)
      pitch = 89.0f;
  if (pitch < -89.0f)
      pitch = -89.0f;

  transform->setRotation({
    Hero::deg2rad(pitch),
    Hero::deg2rad(yaw),
    0.0f}
    );
}

void Player::update()
{
  if(input->keyDown(Hero::System::Input::KeyCode::ESCAPE))
  {
    SDL_SetRelativeMouseMode((SDL_GetRelativeMouseMode() == SDL_TRUE)?SDL_FALSE:SDL_TRUE);
  }

  mouse();
  keyboard();
  Camera::update();
}

void Player::close()
{

}