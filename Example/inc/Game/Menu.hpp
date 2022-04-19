#pragma once

#include"HeroSystems.hpp"
#include"Camera.hpp"

#include"HeroGraphics.hpp"

class Menu : public Hero::System::IScene
{
private:
  Hero::System::Window* window;

  Hero::Cubemap* cubemap;
  Hero::Shader* cubemapShader;
  Hero::Shader* spriteBatchShader;

  Hero::Mesh* stone;
  Hero::Shader* stoneShader;
  Hero::Texture* stoneTexture;
  Hero::Texture* spriteTexture;

  Hero::CameraData* camera;

public:
  void begin() override;
  void update() override;
  void close() override;
};