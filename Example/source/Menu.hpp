#pragma once

#include"Hero/Components/Camera.hpp"
#include"Hero/Core/ISystem.hpp"
#include"Hero/Systems/Window.hpp"
#include"Hero/Graphics/Shader.hpp"
#include"Hero/Graphics/Texture.hpp"
#include"Hero/Graphics/Mesh.hpp"
#include"Hero/Graphics/Cubemap.hpp"
#include"Hero/Systems/Scene.hpp"


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