#include<iostream>

#include"HeroCore.hpp"
#include"HeroSystems.hpp"
#include"HeroGraphics.hpp"
#include"HeroUI.hpp"

#include<cmath>

Hero::Core* core;



class Test : public Hero::ISystem
{
  private:
    Hero::System::Window* window;
    Hero::System::UserInterface* userInterface;
    Hero::System::Input* input;

    Hero::Cubemap* cubemap;
    Hero::Shader* cubemapShader;

    Hero::Terrain* terrain;
    Hero::Shader* terrainShader;

    float yaw = 0.0f;
    float pitch = 0.0f;
    float posy = 0.0f;

    Hero::Transform* system;
  
  public:
    Test(const Hero::Sid& sid) : Hero::ISystem(sid)
    {
    }

    ~Test()
    {

    }

    void init() override
    {
      ISystem::init();
      window = core->getSystem<Hero::System::Window>(SID("window"));
      window->setBackgroundColor((Hero::Color){0,255,255,255});
      input = core->getSystem<Hero::System::Input>(SID("input"));

      glEnable( GL_BLEND );
      glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

      glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT);

      std::vector<std::string> path{
        "bin/assets/skybox/right.jpg",
        "bin/assets/skybox/left.jpg",
        "bin/assets/skybox/top.jpg",
        "bin/assets/skybox/bottom.jpg",
        "bin/assets/skybox/front.jpg",
        "bin/assets/skybox/back.jpg"
      };

      Hero::Matrix4x4 proj = Hero::projectionMatrix(640.0f, 480.0f, 60.0f, 0.01f, 100.0f);

      cubemap = new Hero::Cubemap(path);
      cubemapShader = new Hero::Shader("bin/assets/cubemap.he");
      cubemapShader->bind();
      cubemapShader->setMatrix4f("proj", proj);
      terrain = new Hero::Terrain("bin/assets/iceland_heightmap.png", 0.25f, 16.0f);      
      terrainShader = new Hero::Shader("bin/assets/terrain.he");
      terrainShader->bind();
      terrainShader->setMatrix4f("proj", proj);

      system = new Hero::Transform(1, 1);

      Hero::Camera camera;
    }

    void update() override
    {
      if(input->keyPressed(Hero::System::Input::KeyCode::A))
        yaw -= 50.0f * Hero::Time::getDeltaTime();
      if(input->keyPressed(Hero::System::Input::KeyCode::D))
        yaw += 50.0f * Hero::Time::getDeltaTime();
      if(input->keyPressed(Hero::System::Input::KeyCode::W))
        pitch -= 50.0f * Hero::Time::getDeltaTime();
      if(input->keyPressed(Hero::System::Input::KeyCode::S))
        pitch += 50.0f * Hero::Time::getDeltaTime();

      if(input->keyPressed(Hero::System::Input::KeyCode::LCTRL))
        posy -= 30.0f * Hero::Time::getDeltaTime();
      if(input->keyPressed(Hero::System::Input::KeyCode::SPACE))
        posy += 30.0f * Hero::Time::getDeltaTime();


      float ryaw = Hero::deg2rad(yaw);
      float rpitch = Hero::deg2rad(pitch);
      float x = sinf(ryaw) * cosf(rpitch);
      float y = sinf(rpitch);
      float z = cosf(ryaw) * cosf(rpitch);

      Hero::Float3 target = Hero::addF3({0.0f, posy, 0.0f},{x, y, z});

      Hero::Matrix4x4 view = Hero::lookAtMatrix({0.0f, posy, 0.0f},target, {0.0f, 1.0f, 0.0f});
      
      glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

      terrainShader->bind();
      terrainShader->setMatrix4f("view", view);
      terrain->draw();

      // cubemapShader->bind();
      // cubemapShader->setMatrix4f("view", view);
      // cubemap->draw();

      window->render();
    }

    void close() override
    {
      ISystem::close();

      delete cubemap;
      delete cubemapShader;

      delete terrain;
      delete terrainShader;

      delete system;
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
  core->addSystem(new Hero::System::UserInterface(SID("ui"),SID("window"),SID("input")));

  Hero::System::Event* event = core->getSystem<Hero::System::Event>(SID("event"));
  Hero::System::Window* window = core->getSystem<Hero::System::Window>(SID("window"));
  window->setEvent(Hero::System::WindowEventType::CLOSE, close);
  event->addWindow(window);

  core->addSystem(new Test(SID("test")));

  core->start();

  delete core;

  return 0;
}