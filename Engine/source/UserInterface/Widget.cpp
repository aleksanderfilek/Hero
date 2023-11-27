#include"Widget.hpp"

#include"../Systems/Window.hpp"
#include"../Core/Core.hpp"
#include<iostream>
namespace Hero
{
namespace UI
{

HERO Widget::Widget()
{
  System::Window* window = (System::Window*)Core::getSystem<System::Window>(SID("Window"));
  Int2 Size = window->getSize();
  SetRelativeTransform(Int4(0, 0, Size.x, Size.y));
}

}
}