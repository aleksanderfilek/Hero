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

HERO event(OnResize)
{
  Hero::System::UserInterface* ui = Hero::Core::getSystem<Hero::System::UserInterface>(SID("Ui"));
  Int2 size = *(Int2*)args;
  for(auto widget: ui->widgets)
  {
    widget->SetRelativeTransform(Int4(0, 0, size.x, size.y));
  }
}

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
    it->update(mousePosition, buttonState);
  }

  if(shader == nullptr) return;

  shader->bind();
  spritebatch->begin();
  glDisable(GL_DEPTH_TEST);
  for(auto it: widgets)
  {
    it->draw(spritebatch);
  }
  spritebatch->end();
  window->render();
}

HERO void UserInterface::close()
{
  ISystem::close();
  for(auto widget: widgets)
  {
    delete widget;
  }
  delete spritebatch;
}

HERO bool UserInterface::add(const std::string& name, UI::Widget* widget)
{
  auto result = widgetsMap.insert({name, widget});  

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

  widgets.push_back(widget);

  return true;
}

HERO bool UserInterface::remove(const std::string& name)
{
  UI::Widget* element = widgetsMap[name];
  auto result = widgetsMap.erase(name);
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

  int index;
  for(index = 0; index < widgets.size(); index++)
  {
    if(widgets[index] == element)
    {
      break;
    }
  }

  widgets.erase(widgets.begin() + index);

  return true;
}

HERO UI::Widget* UserInterface::get(const std::string& name)
{
  auto result = widgetsMap.find(name);
  if(result == widgetsMap.end())
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