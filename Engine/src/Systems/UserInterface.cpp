#include"UserInterface.hpp"
#include"Shader.hpp"
#include"Core.hpp"

#include<iostream>
#include<sstream>
#include<utility>

namespace Hero
{
namespace System
{

HERO UserInterface::UserInterface(const Sid& sid, const Sid& windowSid, Shader* _shader) : ISystem(sid)
{
  window = Core::getSystem<Window>(windowSid);
  shader = _shader;

  shader->bind();
  spritebatch = new Spritebatch(*shader, 100, 32);
}

HERO UserInterface::~UserInterface()
{
  delete shader;
  delete spritebatch;
  for(auto widget: widgets)
  {
    delete widget.second;
  }
}

HERO void UserInterface::init()
{
  ISystem::init();
}

HERO void UserInterface::update()
{
  shader->bind();
  for(auto it: widgets)
  {
    it.second->draw(spritebatch);
  }
  window->render();
}

HERO void UserInterface::close()
{
  ISystem::close();
}

HERO bool UserInterface::add(const std::string& name, UI::Widget* element)
{
  auto result = widgets.insert({name, nullptr});  

  if(result.second == false)
  {
    #ifdef HERO_DEBUG
    std::stringstream message;
    message<<"Could not add widget with name: "<<name
      <<". Widget with this name already exists."<<std::endl;
    printMessage(message.str());
    #endif
    return false;
  }
  return true;
}

HERO bool UserInterface::remove(const std::string& name)
{
  auto result = widgets.erase(name);
  if(result == 0)
  {
    #ifdef HERO_DEBUG
    std::stringstream message;
    message<<"Could not remove widget with name: "<<name
      <<". Widget with this name does not exist."<<std::endl;
    printMessage(message.str());
    #endif
    return false;
  }
  return true;
}

HERO UI::Widget* UserInterface::get(const std::string& name)
{
  auto result = widgets.find(name);
  if(result == widgets.end())
  {
    #ifdef HERO_DEBUG
    std::stringstream message;
    message<<"Could not get widget with name: "<<name
      <<". Widget with this name does not exist."<<std::endl;
    printMessage(message.str());
    #endif
    return nullptr;
  }
  return result->second;
}

}
}