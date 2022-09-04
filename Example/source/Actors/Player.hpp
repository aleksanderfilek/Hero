#pragma once 

#include "../Hero/Systems/ActorScene/Actor.hpp"
#include "../Hero/Core/Sid.hpp"
#include "../Components/Camera.hpp"
#include "../Components/Transform.hpp"
#include "../Hero/Systems/Input.hpp"

class Player : public Hero::Actor
{
private:
  CameraComponent Camera;
  TransformComponent Transform;
  Hero::System::Input* input;
  
  float yaw = 0.0f;
  float pitch = 0.0f;

public:
  Player(const Hero::Sid& NewId);

  virtual void Start() override;
  virtual void Update() override;
  virtual void End() override;

  void LookAndMove();
};