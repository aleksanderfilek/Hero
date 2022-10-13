#include "Player.hpp"

#include"../Hero/Core/Core.hpp"
#include"../Hero/ThirdParty/SDL2/SDL.h"
#include"../Hero/Core/Time.hpp"

#define SPEED 40.0f

Player::Player(const Hero::Sid& NewId)
 : Hero::Actor(NewId)
{
  Camera.width = 1280;
  Camera.height = 720;
  Camera.fov = 70.0f;
  Camera.near = 0.1f;
  Camera.far = 1000.0f;
  Hero::CameraInit(Camera);
  Hero::CameraProjectionSet(Camera);
  Hero::CameraViewSet(Camera, Transform);

  input = Hero::Core::getSystem<Hero::System::Input>(SID("input"));
}

void Player::Start()
{

}

void Player::Update()
{
  Hero::TransformUpdate(Transform);
  Hero::CameraViewSet(Camera, Transform);

  LookAndMove();
}

void Player::End()
{

}

void Player::LookAndMove()
{
  if(input->keyDown(Hero::System::Input::KeyCode::ESCAPE))
  {
    SDL_SetRelativeMouseMode((SDL_GetRelativeMouseMode() == SDL_TRUE)?SDL_FALSE:SDL_TRUE);
  }

  int x=0, y=0;
  SDL_GetRelativeMouseState(&x, &y);

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


  Hero::Float3 rotation = {
    Hero::deg2rad(pitch),
    Hero::deg2rad(yaw),
    0.0f};
  TransformRotationSet(Transform, rotation);

  Hero::Float3 forward = TransgormForward(Transform);
  Hero::Float3 right = TransgormRight(Transform);
  Hero::Float3 up = TransgormUp(Transform);

  Hero::Float3 newPosition = Transform.position;

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

  TransformPositionSet(Transform, newPosition);
}