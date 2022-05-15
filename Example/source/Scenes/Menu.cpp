#include"Menu.hpp"

#include"../Components/Player.hpp"
#include"../Components/Mover.hpp"

#include"../Hero/Components/ComponentContext.hpp"
#include"../Hero/Core/Core.hpp"
#include"../Hero/Components/Transform.hpp"
#include"../Hero/Components/Actor.hpp"
#include"../Hero/Components/Sprite.hpp"
#include"../Hero/Core/Random.hpp"
#include"../Hero/Core/Time.hpp"

#include<iostream>
#include<string>

Hero::Actor* Menu::CreateMoverActor(Hero::ComponentContext* context)
{
  Hero::Actor* actor = new Hero::Actor(context);
  actor->AddComponent(SID("Sprite"));
  actor->AddComponent(SID("Mover"));
  Hero::TransformData* t = (Hero::TransformData*)actor->GetComponent(SID("Transform"));
  t->setScale(Hero::Float3(0.05f, 0.05f, 1.0f));
  auto sprite = (Hero::SpriteData*)actor->GetComponent(SID("Sprite"));
  sprite->texture = spriteTexture;
  return actor;
}

void Menu::begin()
{
  Hero::randomSetSeed(0);
  input = Hero::Core::getSystem<Hero::System::Input>(SID("input"));
  window = Hero::Core::getSystem<Hero::System::Window>(SID("window"));
  window->setBackgroundColor((Hero::Color){255,255,255,255});

  context = new Hero::ComponentContext();
  addContext(SID("Main"), context);
  context->Register(SID("Transform"), new Hero::Transform(1000, false));
  context->Register(SID("Camera"), new Hero::Camera(1));
  context->Register(SID("Player"), new Player(1));
  spriteBatchShader = (Hero::Shader*)Hero::Shader::Load("bin/assets/spritebatch.he");
  context->Register(SID("Sprite"), new Hero::Sprite(1000, spriteBatchShader, 100.0f, 1000, 1));
  context->Register(SID("Mover"), new Mover(1000));

  Hero::Actor* actor = new Hero::Actor(context);
  actor->AddComponent(SID("Camera"));
  camera = (Hero::CameraData*)actor->GetComponent(SID("Camera"));
  camera->setProjection(1280, 720, 70.0f, 0.1f, 1000.0f);
  actor->AddComponent(SID("Player"));
  addActor(actor);

  spriteTexture = (Hero::Texture*)Hero::Texture::Load("bin/assets/papaj.he");

  for(int i = 0; i < units; i++)
  {
    addActor(CreateMoverActor(context));
  }

  // std::vector<std::string> path{
  //   "bin/assets/skybox/right.jpg",
  //   "bin/assets/skybox/left.jpg",
  //   "bin/assets/skybox/top.jpg",
  //   "bin/assets/skybox/bottom.jpg",
  //   "bin/assets/skybox/front.jpg",
  //   "bin/assets/skybox/back.jpg"
  // };

  // cubemap = new Hero::Cubemap(path);
  // cubemapShader = (Hero::Shader*)Hero::Shader::Load("bin/assets/cubemap.he");
  //cubemapShader->bind();
  //cubemapShader->setMatrix4f("proj", camera->projection);

  // stone = (Hero::Mesh*)Hero::Mesh::Load("bin/assets/stone.he");
  // stoneShader = (Hero::Shader*)Hero::Shader::Load("bin/assets/standard.he");
  // stoneTexture = spriteTexture;

  // stoneShader->bind();
  // stoneShader->setMatrix4f("proj", camera->projection);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  Hero::System::Window::setDepthTest(true);
}

void Menu::update()
{
  int fps = (int)(1.0f/Hero::Time::getDeltaTime());

  std::string title = "FPS: ";
  title += std::to_string(fps);
  title += " Units: ";
  title += std::to_string(units);

  window->setTitle(title);

  Hero::System::Window::clear();

  timer += Hero::Time::getDeltaTime();
  if(timer > 0.1f)
  {
    units += 1000;
    for(int i = 0; i < 1000; i++)
    {
      addActor(CreateMoverActor(context));
    }
  }

  // cubemapShader->bind();
  // // cubemapShader->setMatrix4f("view", Hero::Matrix4x4(Hero::Matrix3x3(camera->view)));
  // cubemap->draw();

  // Hero::Matrix4x4 stoneModel = Hero::TRS({0.0f, 0.0f, 10.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
  // stoneShader->bind();
  // stoneShader->setMatrix4f("model", stoneModel);
  // // stoneShader->setMatrix4f("view", camera->view);
  // stoneTexture->bind();
  // stone->draw();

  window->render();

  IScene::update();
}

void Menu::close()
{
  // delete cubemap;
  // Hero::Shader::Unload(cubemapShader);
  // delete cubemapShader;

  // Hero::Shader::Unload(stoneShader);
  // Hero::Mesh::Unload(stone);
  // delete stone;
  // delete stoneTexture;
  // delete stoneShader;

  Hero::Shader::Unload(spriteBatchShader);
  Hero::Texture::Unload(spriteTexture);
}