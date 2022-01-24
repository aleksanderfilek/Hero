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
    Hero::Spritesheet* spritesheet;
    Hero::Spritebatch* spritebatch;
  public:
    Test(const Hero::Sid& sid) : Hero::ISystem(sid)
    {
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

      shader = new Hero::Shader("bin/assets/spritebatch.he");
      shader->bind();
      uint32_t viewLoc = shader->getUniformLocation("view");

      spritesheet = new Hero::Spritesheet("bin/assets/test.he");
      Hero::Matrix4x4 view = Hero::pixelScreenMatrix(640, 480, 0.00f, 1.0f);
      glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view.col[0].x);

      spritebatch = new Hero::Spritebatch(*shader, 10, 10);

    }

    void update() override
    {
      glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

      spritebatch->begin();

      Hero::Int2 position = {0,0};
      Hero::Int2 size = {200,200};
      spritebatch->drawTexture(spritesheet->getTexture(), position, size);

      spritebatch->end();

      window->render();
    }

    void close() override
    {
      ISystem::close();

      delete shader;
      delete spritesheet;
      delete spritebatch;
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