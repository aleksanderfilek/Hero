#include"Menu.hpp"
#include"Player.hpp"
#include"ComponentContext.hpp"
#include"Core.hpp"
#include"Transform.hpp"
#include"Actor.hpp"
#include"Sprite.hpp"
#include<iostream>

void Menu::begin()
{
  window = Hero::Core::getSystem<Hero::System::Window>(SID("window"));
  window->setBackgroundColor((Hero::Color){255,255,255,255});

  Hero::ComponentContext* context = new Hero::ComponentContext();
  addContext(SID("Main"), context);
  context->Register(SID("Transform"), new Hero::Transform(1));
  context->Register(SID("Camera"), new Hero::Camera(1));
  context->Register(SID("Player"), new Player(1));
  spriteBatchShader = (Hero::Shader*)Hero::Shader::Load("bin/assets/spritebatch.he");
  context->Register(SID("Sprite"), new Hero::Sprite(1,spriteBatchShader));

  Hero::Actor* actor = new Hero::Actor(context);
  actor->AddComponent(SID("Camera"));
  camera = (Hero::CameraData*)actor->GetComponent(SID("Camera"));
  camera->setProjection(1280, 720, 70.0f, 0.1f, 1000.0f);
  actor->AddComponent(SID("Player"));
  addActor(actor);

  spriteTexture = new Hero::Texture("bin/assets/Bricks.png");

  Hero::Actor* actor2 = new Hero::Actor(context);
  actor2->AddComponent(SID("Sprite"));
  auto sprite = (Hero::SpriteData*)actor2->GetComponent(SID("Sprite"));
  sprite->texture = spriteTexture;
  addActor(actor2);

  std::vector<std::string> path{
    "bin/assets/skybox/right.jpg",
    "bin/assets/skybox/left.jpg",
    "bin/assets/skybox/top.jpg",
    "bin/assets/skybox/bottom.jpg",
    "bin/assets/skybox/front.jpg",
    "bin/assets/skybox/back.jpg"
  };

  cubemap = new Hero::Cubemap(path);
  cubemapShader = (Hero::Shader*)Hero::Shader::Load("bin/assets/cubemap.he");
  //cubemapShader->bind();
  //cubemapShader->setMatrix4f("proj", camera->projection);

  stone = (Hero::Mesh*)Hero::Mesh::Load("bin/assets/stone.he");
  stoneShader = (Hero::Shader*)Hero::Shader::Load("bin/assets/standard.he");
  stoneTexture = new Hero::Texture("bin/assets/stone.jpg");

  // stoneShader->bind();
  // stoneShader->setMatrix4f("proj", camera->projection);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  Hero::System::Window::setDepthTest(true);
}

void Menu::update()
{
  Hero::System::Window::clear();

  cubemapShader->bind();
  // cubemapShader->setMatrix4f("view", Hero::Matrix4x4(Hero::Matrix3x3(camera->view)));
  cubemap->draw();

  Hero::Matrix4x4 stoneModel = Hero::TRS({0.0f, 0.0f, 10.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
  stoneShader->bind();
  stoneShader->setMatrix4f("model", stoneModel);
  // stoneShader->setMatrix4f("view", camera->view);
  stoneTexture->bind();
  stone->draw();

  window->render();

  IScene::update();
}

void Menu::close()
{
  delete cubemap;
  Hero::Shader::Unload(cubemapShader);
  delete cubemapShader;

  Hero::Shader::Unload(stoneShader);
  Hero::Mesh::Unload(stone);
  delete stone;
  delete stoneTexture;
  delete stoneShader;

  Hero::Shader::Unload(spriteBatchShader);
  delete spriteBatchShader;
  delete spriteTexture;
}