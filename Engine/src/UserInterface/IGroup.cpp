#include"IGroup.hpp"

namespace Hero
{
namespace UI
{

HERO IGroup::~IGroup()
{
  for(auto& child: children)
  {
    delete child.second;
  }
}

HERO void IGroup::update(Int2 mousePosition)
{
  bool result = pointBoxIntersection(mousePosition, absolutePosition, size);
  if(!lastTick && !result)
  {
    lastTick = result;
    return;
  }

  for(auto it: children)
  {
    it.second->update(mousePosition);
  } 

  lastTick = result;
}

HERO void IGroup::draw(Spritebatch* spritebatch)
{
  if(!visible) return;

  for(auto it: children)
  {
    it.second->draw(spritebatch);
  }
}

HERO bool IGroup::add(const std::string& name, IElement* element)
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

  element->parent = this;
  
  recalculate();

  return true;
}

HERO bool IGroup::remove(const std::string& name)
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

HERO void IGroup::recalculate()
{
  int maxX = absolutePosition.x;
  int maxY = absolutePosition.y;

  for(auto& child: children)
  {
    IElement* element = child.second;
    int x = element->absolutePosition.x + element->size.x;
    int y = element->absolutePosition.y + element->size.y;

    if(x > maxX) maxX = x;
    if(y > maxY) maxY = y;
  }

  size = { maxX, maxY };
}

HERO void IGroup::setPosition(Int2 _position)
{
  IElement::setPosition(_position);

  recalculate();
}

}
}