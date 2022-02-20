#pragma once

#include"Components/Camera.hpp"
#include"Systems/Input.hpp"
#include"Graphics/Shader.hpp"

class Player : public Hero::Camera
{
private:
  Hero::System::Input* input;

  float yaw = 0.0f;
  float pitch = 0.0f;

  void keyboard();
  void mouse();
public:
  Hero::Shader* shader;

  Player(int _width, int _height, float _FOV, float _near, float _far);

  void begin() override;
  void update() override;
  void close() override;
};