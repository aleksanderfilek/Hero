#pragma once

#include"../Hero/Systems/ActorScene/Scene.hpp"
#include"../Hero/Systems/Window.hpp"
#include"../Hero/Graphics/Shader.hpp"
#include"../Hero/Graphics/Mesh.hpp"
#include"../Hero/Systems/Input.hpp"

class Game : public Hero::Scene
{
private:
  Hero::System::Window* window;
  Hero::System::Input* input;

public:
  void Start() override;
  void Update() override;
  void End() override;
};