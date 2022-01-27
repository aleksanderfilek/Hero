#include<iostream>

#include"HeroCore.hpp"
#include"HeroSystems.hpp"
#include"HeroGraphics.hpp"
#include"HeroUI.hpp"

Hero::Core* core;

class Test : public Hero::ISystem
{
  private:
    Hero::System::Window* window;
    Hero::System::UserInterface* userInterface;
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

      userInterface = core->getSystem<Hero::System::UserInterface>(SID("ui"));
      Hero::Shader* shader = new Hero::Shader("bin/assets/spritebatch.he");
      userInterface->setShader(shader);

      Hero::Matrix4x4 view = Hero::pixelScreenMatrix(640, 480, 0.0f, 1.0f);
      glUniformMatrix4fv(shader->getUniformLocation("view"), 1, GL_FALSE, &view.col[0].x);

      Hero::UI::Widget* widget = new Hero::UI::Widget();
      Hero::UI::Image* image = new Hero::UI::Image();
      Hero::UI::Label* label = new Hero::UI::Label();
      Hero::UI::Canvas* canvas = new Hero::UI::Canvas();
      canvas->setPosition({100,100});

      image->setTexture(new Hero::Texture("bin/assets/Bricks.png"));
      image->setSize({100,100});
      image->setPosition({100,0});
      label->setFont(new Hero::Font("bin/assets/arial.ttf",28));
      label->setText("Hello, World!");
      label->setSize({200,200});
      label->setAlligment(Hero::UI::Alligment::CENTER);
      label->apply();

      canvas->add("image", image);
      canvas->add("label", label);
      widget->add("canvas", canvas);
      userInterface->add("main", widget);

      glEnable( GL_BLEND );
      glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    }

    void update() override
    {
      glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

      window->render();
    }

    void close() override
    {
      ISystem::close();

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
  core->addSystem(new Hero::System::UserInterface(SID("ui"),SID("window")));

  Hero::System::Event* event = core->getSystem<Hero::System::Event>(SID("event"));
  Hero::System::Window* window = core->getSystem<Hero::System::Window>(SID("window"));
  window->setEvent(Hero::System::WindowEventType::CLOSE, close);
  event->addWindow(window);

  core->addSystem(new Test(SID("test")));

  core->start();

  delete core;

  return 0;
}