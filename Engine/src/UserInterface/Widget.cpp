#include"Widget.hpp"

namespace Hero
{
namespace UI
{
  
HERO void Widget::draw(Spritebatch* spritebatch)
{
  if(!visible) return;

  for(auto it: children)
  {
    it.second->draw(spritebatch);
  }
}

}
}