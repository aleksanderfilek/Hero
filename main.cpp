#include<iostream>

#include"Engine/inc/Hero.hpp"
#include"Engine/inc/Core/HeroEvent.hpp"
#include"Engine/inc/Systems/HeroWindowSystem.hpp"
#include"Engine/inc/Systems/HeroEventSystem.hpp"

Hero::Core* core = nullptr;


event(close)
{
    core->close();
}


class Test: public Hero::ISystem
{
    public:
        Test(Hero::Sid sid):ISystem(sid){}
        ~Test(){}

        void init() override
        {
            ISystem::init();
        }

        void update() override
        {
        }

        void close() override
        {
            ISystem::close();
        }
};

int main()
{
    core = new Hero::Core();
    core->addSystem(new Test(SID("Test")));
    core->addSystem(new Hero::System::Window(SID("Window"), "Hello", 640, 480));
    core->addSystem(new Hero::System::Event(SID("Event")));

    Hero::System::Window* window = (Hero::System::Window*)core->getSystem(SID("Window"));
    window->setEvent(Hero::System::WindowEventType::CLOSE, close);
    Hero::System::Event* event = (Hero::System::Event*)core->getSystem(SID("Event"));
    event->addWindow(window);

    core->start();

    delete core;
   
    return 0;
}