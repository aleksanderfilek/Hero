#include"Widget.hpp"

namespace Hero
{
namespace UI
{

HERO Widget::Widget()
{
  
}

HERO Widget::~Widget()
{
  for(auto it: children)
  {
    delete it.second;
  }
}

HERO void Widget::draw(Spritebatch* spritebatch)
{
  for(auto it: children)
  {
    it.second->draw(spritebatch);
  }
}

HERO bool Widget::add(const std::string& name, IElement* element)
{
  return true;
}

HERO bool Widget::remove(const std::string& name)
{
  return true;
}

}
}