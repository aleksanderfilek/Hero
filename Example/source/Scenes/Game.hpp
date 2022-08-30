#pragma once

#include"../Hero/Systems/ActorScene/ActorScene.hpp"
#include"../Hero/Systems/Window.hpp"
#include"../Hero/Systems/Input.hpp"

class Game : public Hero::ActorScene
{
private:
  Hero::System::Window* window;
  Hero::System::Input* input;

public:
  void Start() override;
  void Update() override;
  void End() override;
};