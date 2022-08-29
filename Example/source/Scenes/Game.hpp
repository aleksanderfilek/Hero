#pragma once

#include"../Hero/Systems/Window.hpp"
#include"../Hero/Systems/Scene.hpp"
#include"../Hero/Systems/Input.hpp"

class Game : public Hero::System::IScene
{
private:
  Hero::System::Window* window;
  Hero::System::Input* input;

public:
  void begin() override;
  void update() override;
  void close() override;
};