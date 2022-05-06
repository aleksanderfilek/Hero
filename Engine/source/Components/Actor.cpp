#include"Actor.hpp"
#include"IComponent.hpp"
#include"Transform.hpp"
#include"ComponentContext.hpp"

namespace Hero
{

HERO Actor::Actor(ComponentContext* Context)
  : context(Context)
{
  AddComponent(SID("Transform"));
}

HERO Actor::~Actor()
{
  for(auto pair: components)
  {
    context->Get(pair.first)->removeComponent(pair.second);
  }
}

HERO void Actor::AddComponent(const Sid& sid)
{
  ChunkArrayIndex index =  context->Get(sid)->addComponent(this);
  components.insert({sid, index});
}

HERO bool Actor::RemoveComponent(const Sid& sid)
{
  auto result = components.find(sid);
  if(result == components.end()) 
    return false;

  context->Get(sid)->removeComponent(result->second);
  components.erase(result);

  return true;
}

HERO IComponent* Actor::GetComponent(const Sid& sid)
{
  auto result = components.find(sid);
  if(result == components.end()) 
    return nullptr;

  return context->Get(sid)->getComponent(result->second);
}

}