#include<iostream>

#include"HeroCore.hpp"
#include"HeroSystems.hpp"
#include"HeroGraphics.hpp"

#include<cmath>

#define SPEED 10

Hero::Core* core;

class Test : public Hero::ISystem
{
  private:
    Hero::System::Input* input;
    Hero::System::Window* window;
    Hero::Shader* shader;
    Hero::Mesh* mesh;
    Hero::Texture* texture;

    Hero::Matrix4x4 proj, view, model;

    Hero::Float3 eye = Float3zero;
    float angle = 0.0f;
  public:
    Test(const Hero::Sid& sid) : Hero::ISystem(sid)
    {
      printMessage("Siema");
      priority = 255;
    }

    ~Test()
    {

    }

    void init() override
    {
      ISystem::init();
      window = (Hero::System::Window*)core->getSystem(SID("window"));
      window->setBackgroundColor((Hero::Color){0,255,255,255});
      input = (Hero::System::Input*)core->getSystem(SID("input"));

      shader = new Hero::Shader("bin/assets/standard.he");
      shader->bind();
      proj = Hero::projectionMatrix(640.0f, 480.0f, 60.0f, 0.1f, 1000.0f);
      model = Mat4x4Identity;
      Hero::translateM4x4(&model, {0.0f, 0.0f, 10.0f});
      glUniformMatrix4fv(glGetUniformLocation(shader->getGlId(), "proj"), 1, GL_FALSE, &proj.col[0].x);
      glUniformMatrix4fv(glGetUniformLocation(shader->getGlId(), "model"), 1, GL_FALSE, &model.col[0].x);

      mesh = new Hero::Mesh("bin/assets/stone.he");

      texture = new Hero::Texture("bin/assets/stone.jpg",(uint8_t)Hero::TextureFlag::LINEAR | (uint8_t)Hero::TextureFlag::NO_MIPMAP);
      texture->bind();
    }

    void update() override
    {
      if(input->keyPressed(Hero::System::Input::KeyCode::A))
      eye.x += SPEED * Hero::Time::getDeltaTime();
      if(input->keyPressed(Hero::System::Input::KeyCode::D))
      eye.x -= SPEED * Hero::Time::getDeltaTime();

      if(input->keyPressed(Hero::System::Input::KeyCode::W))
      eye.z += SPEED * Hero::Time::getDeltaTime();
      if(input->keyPressed(Hero::System::Input::KeyCode::S))
      eye.z -= SPEED * Hero::Time::getDeltaTime();

      if(input->keyPressed(Hero::System::Input::KeyCode::SPACE))
      eye.y += SPEED * Hero::Time::getDeltaTime();
      if(input->keyPressed(Hero::System::Input::KeyCode::LCTRL))
      eye.y -= SPEED * Hero::Time::getDeltaTime();

      if(input->keyPressed(Hero::System::Input::KeyCode::E))
      angle -= 30.0f * Hero::Time::getDeltaTime();
      if(input->keyPressed(Hero::System::Input::KeyCode::Q))
      angle += 30.0f * Hero::Time::getDeltaTime();

      float a = Hero::deg2rad(angle);
      float tx = sinf(a);
      float tz = cosf(a);
      Hero::Float3 dir = {tx, 0.0f, tz};
      dir = Hero::normalizeF3(dir);

      Hero::Float3 target = Hero::addF3(eye, dir);

      view = Hero::lookAtMatrix(eye,target,{0.0f, 1.0f, 0.0f});
      glUniformMatrix4fv(glGetUniformLocation(shader->getGlId(), "view"), 1, GL_FALSE, &view.col[0].x);

      glClear(GL_COLOR_BUFFER_BIT);

      mesh->draw();

      window->render();
    }

    void close() override
    {
      ISystem::close();

      delete shader;
      delete mesh;
      delete texture;
    }
};

event(close)
{
  Hero::Core::close();
}

int SDL_main(int argc, char* argv[])
{
  core = new Hero::Core();

  core->addSystem(new Hero::System::Window(SID("window"), "Example", 640, 480));
  core->addSystem(new Hero::System::Event(SID("event")));
  core->addSystem(new Hero::System::Input(SID("input")));
  Hero::System::Event* event = (Hero::System::Event*)core->getSystem(SID("event"));
  Hero::System::Window* window = (Hero::System::Window*)core->getSystem(SID("window"));
  window->setEvent(Hero::System::WindowEventType::CLOSE, close);
  event->addWindow(window);

  core->addSystem(new Test(SID("test")));

  core->start();

  delete core;

  return 0;
}