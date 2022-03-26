#include"Menu.hpp"
#include"Player.hpp"

#include"Core.hpp"
#include"Transform.hpp"
#include"Actor.hpp"

#include<iostream>

void Menu::begin()
{
  window = Hero::Core::getSystem<Hero::System::Window>(SID("window"));
  window->setBackgroundColor((Hero::Color){255,255,255,255});

  addSystem(new Hero::Transform(1));
  addSystem(new Hero::Camera(1));
  addSystem(new Player(1));

  Hero::Actor* actor = new Hero::Actor();
  actor->addComponent<Hero::Camera>();
  camera = (Hero::CameraData*)actor->getComponent<Hero::Camera>();
  camera->setPerspective(1280, 720, 70.0f, 0.1f, 100.0f);
  actor->addComponent<Player>();

  addActor(actor);

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
  cubemapShader->setMatrix4f("proj", camera->projection);

  stone = new Hero::Mesh("bin/assets/stone.he");
  stoneShader = new Hero::Shader("bin/assets/standard.he");
  stoneTexture = new Hero::Texture("bin/assets/stone.jpg");

  stoneShader->bind();
  stoneShader->setMatrix4f("proj", camera->projection);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  Hero::System::Window::setDepthTest(true);
}

void Menu::update()
{
  IScene::update();

  Hero::System::Window::clear();

  // std::cout<<camera->transform->forward()<<std::endl;
  // std::cout<<camera->view<<std::endl;

  cubemapShader->bind();
  cubemapShader->setMatrix4f("view", Hero::Matrix4x4(Hero::Matrix3x3(camera->view)));
  cubemap->draw();

  Hero::Matrix4x4 stoneModel = Hero::TRS({0.0f, 0.0f, 10.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
  stoneShader->bind();
  stoneShader->setMatrix4f("model", stoneModel);
  stoneShader->setMatrix4f("view", camera->view);
  stoneTexture->bind();
  stone->draw();

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