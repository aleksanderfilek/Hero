#pragma once

#include"HeroSystems.hpp"

#include"HeroGraphics.hpp"

class Menu : public Hero::System::IScene
{
private:
  Hero::System::Window* window;

  class Player* camera = nullptr;

  Hero::Cubemap* cubemap;
  Hero::Shader* cubemapShader;

  Hero::Mesh* stone;
  Hero::Shader* stoneShader;
  Hero::Texture* stoneTexture;

public:
  void begin() override;
  void update() override;
  void close() override;
};