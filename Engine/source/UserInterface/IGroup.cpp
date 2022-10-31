#include"IGroup.hpp"

#include<iostream>

namespace Hero
{
namespace UI
{

HERO IGroup::~IGroup()
{
  for(auto& child: children)
  {
    delete child;
  }
}

HERO void IGroup::update(Int2 mousePosition, uint8_t buttonState)
{  
  bool result = visible && pointBoxIntersection(mousePosition, GetAbsolutePosition(), GetAbsoluteSize());
  
  if(!lastTick && !result)
  {
    lastTick = result;
    return;
  }

  for(auto it: children)
  {
    it->update(mousePosition, buttonState);
  } 
  IElement::update(mousePosition, buttonState);

  lastTick = result;
}

HERO void IGroup::draw(Spritebatch* spritebatch)
{
  if(!visible) return;

  for(auto it: children)
  {
    it->draw(spritebatch);
  }
}

HERO bool IGroup::add(const std::string& name, IElement* element)
{
  auto result = childMap.insert({name, element});  

  if(result.second == false)
  {
    #ifdef HERO_DEBUG
    std::cout<<"Could not add element with name: "<<name
      <<". Element with this name already exists."<<std::endl;
    #endif
    return false;
  }

  children.push_back(element);
  element->parent = this;
  element->UpdateAbsoluteTransform();
  
  return true;
}

HERO bool IGroup::remove(const std::string& name)
{
  IElement* element = childMap[name];
  auto result = childMap.erase(name);

  if(result == 0)
  {
    #ifdef HERO_DEBUG
    std::cout<<"Could not remove element with name: "<<name
      <<". Element with this name does not exist."<<std::endl;
    #endif
    return false;
  }

  int index;
  for(index = 0; index < children.size(); index++)
  {
    if(children[index] == element)
    {
      break;
    }
  }

  children.erase(children.begin() + index);

  return true;
}


}
}