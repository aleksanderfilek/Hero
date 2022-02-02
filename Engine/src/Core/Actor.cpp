#include"Actor.hpp"
#include"IComponent.hpp"

namespace Hero
{

HERO Actor::~Actor()
{
  for(auto pair: components)
  {
    pair.first->removeComponent(pair.second);
  }
}

}