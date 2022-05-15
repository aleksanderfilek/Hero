#include"Widget.hpp"

#include"../Systems/Window.hpp"
#include"../Core/Core.hpp"

namespace Hero
{
namespace UI
{

HERO Widget::Widget()
{
  System::Window* window = Core::getSystem(SID("Window"));

  setSize(window->getSize());
}

}
}