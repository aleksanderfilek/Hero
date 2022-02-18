#include"Player.hpp"

#include"Core/Core.hpp"
#include"Core/Math.hpp"
#include"Core/Time.hpp"
#include"Systems/Window.hpp"
#include"ThirdParty.hpp"
#include<iostream>
#include"cmath"

#define SPEED 10.0f

Player::Player(int _width, int _height, float _FOV, float _near, float _far)
:Camera( _width,  _height,  _FOV,  _near,  _far)
{
  input = Hero::Core::getSystem<Hero::System::Input>(SID("input"));
    auto window = Hero::Core::getSystem<Hero::System::Window>(SID("window"));
  SDL_WarpMouseInWindow(window->getWindow(), 320 ,240);
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
  int x, y;
  input->getMousePosition(&x, &y);

  float xpos = (float)x;
  float ypos = (float)y;

  float xoffset = xpos - 320;
  float yoffset = 240 - ypos; // reversed since y-coordinates go from bottom to top

  float sensitivity = 0.1f; // change this value to your liking
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

  auto window = Hero::Core::getSystem<Hero::System::Window>(SID("window"));
  SDL_WarpMouseInWindow(window->getWindow(), 320 ,240);
}

void Player::update()
{
  mouse();
  keyboard();
  Camera::update();
}

void Player::close()
{

}