#include<iostream>

#include"HeroCore.hpp"
#include"HeroSystems.hpp"
#include"HeroGraphics.hpp"

Hero::Core* core;

class Test : public Hero::ISystem
{
  private:
    Hero::System::Window* window;
    Hero::Shader* shader;
    Hero::Mesh * mesh;
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

      shader = new Hero::Shader("bin/assets/standard.he");

      std::vector<Hero::MeshBuffer<float>> buffers;
      Hero::MeshBuffer<float> position;
      position.type = Hero::BufferType::vec2;
      position.array = new float[6]{0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.0f};
      position.length = 6;
      buffers.push_back(position);

      Hero::MeshBuffer<int> indices;
      indices.array = new int[3]{0,1,2};
      indices.length = 3;

      mesh = new Hero::Mesh("triangle", buffers, indices);
    }

    void update() override
    {
      glClear(GL_COLOR_BUFFER_BIT);

      mesh->draw();

      window->render();
    }

    void close() override
    {
      ISystem::close();

      delete shader;
      delete mesh;
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
  Hero::System::Event* event = (Hero::System::Event*)core->getSystem(SID("event"));
  Hero::System::Window* window = (Hero::System::Window*)core->getSystem(SID("window"));
  window->setEvent(Hero::System::WindowEventType::CLOSE, close);
  event->addWindow(window);

  core->addSystem(new Test(SID("test")));

  core->start();

  delete core;

  return 0;
}