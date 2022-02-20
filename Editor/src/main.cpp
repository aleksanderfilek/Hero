#include"HeroCore.hpp"
#include"HeroSystems.hpp"
#include"HeroGraphics.hpp"
#include"UserInterface/Font.hpp"

#include"MainToolBarWidget.hpp"
#include"Resources.hpp"

Hero::Core* core;

class Clear : public Hero::ISystem
{
public:
  Clear(const Hero::Sid& sid):ISystem(sid){}

  void update() override
  {
    glClear(GL_COLOR_BUFFER_BIT);
  }
};

event(close)
{
  Hero::Core::close();
}

int main(int argc, char* argv[])
{
  core = new Hero::Core();

  core->addSystem(new Hero::System::Window(SID("window"), "Editor", 640, 480));
  core->addSystem(new Hero::System::Event(SID("event")));
  core->addSystem(new Hero::System::Input(SID("input")));
  core->addSystem(new Hero::System::UserInterface(SID("ui"),SID("window"),SID("input")));
  core->addSystem(new Resources(SID("resources")));

  //core->addSystem(new Hero::System::Scene(SID("scene"), new Menu()));
  core->addSystem(new Clear(SID("clear")));

  {
    Hero::System::Event* event = core->getSystem<Hero::System::Event>(SID("event"));
    Hero::System::Window* window = core->getSystem<Hero::System::Window>(SID("window"));
    window->setEvent(Hero::System::WindowEventType::CLOSE, close);
    event->addWindow(window);

    window->setBackgroundColor((Hero::Color){255,255,255,255});

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  }

  {
    auto ui = core->getSystem<Hero::System::UserInterface>(SID("ui"));
    auto resources = Hero::Core::getSystem<Resources>(SID("resources"));

    Hero::Font* font = new Hero::Font("bin/assets/Montserrat-Light.ttf", 14);
    resources->add(SID("montserrat28"), font);

    Hero::Shader* shader = new Hero::Shader("bin/assets/spritebatch.he");
    shader->bind();
    shader->setMatrix4f("view", Hero::pixelScreenMatrix(640,480,0.0f, 1.0f));
    ui->setShader(shader);

    ui->add("MainToolBar", new MainToolBarWidget());
  }

  core->start();

  delete core;

  return 0;
}