#include"UserInterface.hpp"
#include"../Core/Core.hpp"
#include"../Graphics/Shader.hpp"
#include"Window.hpp"
#include"Input.hpp"

#include<iostream>
#include<sstream>
#include<utility>

namespace Hero
{
namespace System
{

HERO UserInterface::UserInterface(const Sid& sid, const Sid& windowSid, 
  const Sid& inputSid) : ISystem(sid)
{
  window = Core::getSystem<Window>(windowSid);
  input = Core::getSystem<Input>(inputSid);

  spritebatch = new Spritebatch(100, 32);
}

HERO UserInterface::~UserInterface()
{
}

HERO void UserInterface::init()
{
  ISystem::init();
}

HERO void UserInterface::update()
{
  Int2 mousePosition = input->getMousePosition();
  uint8_t buttonState = input->getMouseState(Input::Mouse::Left);

  for(auto it: widgets)
  {
    it.second->update(mousePosition, buttonState);
  }

  if(shader == nullptr) return;

  shader->bind();
  spritebatch->begin();
  for(auto it: widgets)
  {
    it.second->draw(spritebatch);
  }
  spritebatch->end();
  window->render();
}

HERO void UserInterface::close()
{
  ISystem::close();
  delete shader;
  delete spritebatch;
  for(auto widget: widgets)
  {
    delete widget.second;
  }
}

HERO bool UserInterface::add(const std::string& name, UI::Widget* widget)
{
  auto result = widgets.insert({name, widget});  

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

HERO void UserInterface::setShader(Shader* _shader)
{
  shader = _shader;
  spritebatch->setShader(_shader);
}

}
}