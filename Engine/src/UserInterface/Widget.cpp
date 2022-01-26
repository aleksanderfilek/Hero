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
  if(!visible) return;

  for(auto it: children)
  {
    it.second->draw(spritebatch);
  }
}

HERO bool Widget::add(const std::string& name, IElement* element)
{
  auto result = children.insert({name, element});  

  if(result.second == false)
  {
    #ifdef HERO_DEBUG
    std::cout<<"Could not add element with name: "<<name
      <<". Element with this name already exists."<<std::endl;
    #endif
    return false;
  }
  return true;
}

HERO bool Widget::remove(const std::string& name)
{
  auto result = children.erase(name);
  if(result == 0)
  {
    #ifdef HERO_DEBUG
    std::cout<<"Could not remove element with name: "<<name
      <<". Element with this name does not exist."<<std::endl;
    #endif
    return false;
  }
  return true;
}

}
}