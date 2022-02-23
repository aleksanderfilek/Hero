#include"Menu.hpp"
#include"Pistol.hpp"
#include"Player.hpp"

#include"Core.hpp"
#include"Components/Transform.hpp"

#include<iostream>

void Menu::begin()
{
  window = Hero::Core::getSystem<Hero::System::Window>(SID("window"));
  window->setBackgroundColor((Hero::Color){255,255,255,255});

  addSystem(new Hero::Transform(2));

  camera = new Player(640, 480, 70, 0.1f, 100.0f);

  addActor(camera);

  std::vector<std::string> path{
    "bin/assets/skybox/right.jpg",
    "bin/assets/skybox/left.jpg",
    "bin/assets/skybox/top.jpg",
    "bin/assets/skybox/bottom.jpg",
    "bin/assets/skybox/front.jpg",
    "bin/assets/skybox/back.jpg"
  };

  cubemap = new Hero::Cubemap(path);
  cubemapShader = new Hero::Shader("bin/assets/cubemap.he");
  cubemapShader->bind();
  cubemapShader->setMatrix4f("proj", camera->getProjectionMatrix());

  stone = new Hero::Mesh("bin/assets/stone.he");
  stoneShader = new Hero::Shader("bin/assets/standard.he");
  stoneTexture = new Hero::Texture("bin/assets/stone.jpg");

  stoneShader->bind();
  stoneShader->setMatrix4f("proj", camera->getProjectionMatrix());

  camera->shader = stoneShader;

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  glEnable(GL_DEPTH_TEST);  
}

void Menu::update()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  cubemapShader->bind();
  cubemapShader->setMatrix4f("view", Hero::convertToM4(Hero::convertToM3(camera->getViewMatrix())));
  cubemap->draw();

  // Hero::Matrix4x4 stoneModel = Hero::Matrix4x4::identity();
  // Hero::translateM4x4(&stoneModel, {0.0f, 0.0f, 10.0f});
  Hero::Matrix4x4 stoneModel = Hero::TRS({0.0f, 0.0f, 10.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
  stoneShader->bind();
  stoneShader->setMatrix4f("model", stoneModel);
  stoneShader->setMatrix4f("view", camera->getViewMatrix());
  stoneTexture->bind();
  stone->draw();

  IScene::update();

  window->render();
}

void Menu::close()
{
  delete cubemap;
  delete cubemapShader;

  delete stone;
  delete stoneTexture;
  delete stoneShader;
}