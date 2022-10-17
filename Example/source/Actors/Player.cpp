#include "Player.hpp"

#include"../Hero/Core/Core.hpp"
#include"../Hero/ThirdParty/SDL2/SDL.h"
#include"../Hero/Core/Time.hpp"
#include "../Hero/Components/Camera.hpp"

#include<iostream>

#define SPEED 40.0f

Player::Player(const Hero::Sid& NewId)
 : Hero::Actor(NewId)
{
  input = Hero::Core::getSystem<Hero::System::Input>(SID("input"));
}

void Player::Start()
{
  Hero::Actor::Start();

  Hero::Camera* camera = new Hero::Camera();
  camera->SetSize({1280,720});
  camera->SetFov(70.0f);
  camera->SetNearFarPlane(0.1f, 1000.0f);
  AddComponent(camera);
}

void Player::Update()
{
  Hero::Actor::Update();

  LookAndMove();
}

void Player::End()
{
  Hero::Actor::End();
}

void Player::LookAndMove()
{
  if(input->keyDown(Hero::System::Input::KeyCode::ESCAPE))
  {
    input->setRelativeMode(!input->isInRelativeMode());
  }

  Hero::Int2 delta = input->getMouseDeltaPosition();
  float xpos = (float)delta.x;
  float ypos = (float)delta.y;

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


  Hero::Float3 rotation = {
    Hero::deg2rad(yaw),
    Hero::deg2rad(pitch),
    0.0f};
  SetRotation(Hero::Quaternion(rotation));

  Hero::Float3 forward = GetRotation().GetForwardVector();
  Hero::Float3 right = GetRotation().GetRightVector();
  Hero::Float3 up = GetRotation().GetUpVector();

  Hero::Float3 newPosition = GetPosition();

  if(input->keyPressed(Hero::System::Input::KeyCode::W))
  {
    newPosition += forward * SPEED * Hero::Time::getDeltaTime();
  }
  else if(input->keyPressed(Hero::System::Input::KeyCode::S))
  {
    newPosition -= forward * SPEED * Hero::Time::getDeltaTime();
  }

  if(input->keyPressed(Hero::System::Input::KeyCode::A))
  {
    newPosition -= right * SPEED * Hero::Time::getDeltaTime();
  }
  else if(input->keyPressed(Hero::System::Input::KeyCode::D))
  {
    newPosition += right * SPEED * Hero::Time::getDeltaTime();    
  }

  if(input->keyPressed(Hero::System::Input::KeyCode::SPACE))
  {
    newPosition += up * SPEED * Hero::Time::getDeltaTime();
  }
  else if(input->keyPressed(Hero::System::Input::KeyCode::LCTRL))
  {
    newPosition -= up * SPEED * Hero::Time::getDeltaTime();
  }

  SetPosition(newPosition);
}

Hero::Actor* Player::Clone()
{
    Hero::Actor* actor = new Player(GetName());
    actor->SetTransform(actor->GetTransform());
    return actor;
}