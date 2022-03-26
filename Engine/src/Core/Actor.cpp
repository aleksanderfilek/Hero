#include"Actor.hpp"
#include"IComponent.hpp"
#include"Components/Transform.hpp"

#include<iostream>

namespace Hero
{

// HERO Actor::Actor()
// {
//   addComponent<Transform>();
// }

HERO Actor::~Actor()
{
  for(auto pair: components)
  {
    pair.first->removeComponent(pair.second);
  }
}

}