#pragma once

#include"../Core/ISystem.hpp"
#include"../UserInterface/Widget.hpp"
#include"../Graphics/Spritebatch.hpp"
#include"../Core/Events.hpp"

#include<map>
#include<vector>
#include<string>

namespace Hero
{
namespace System
{ 

HERO event(OnResize);

class Window;
class Input;

class UserInterface : public ISystem
{
// events
friend void OnResize(void* object, void* args, int argc);

private:
  Window* window = nullptr;
  Input* input = nullptr;

  std::map<std::string, UI::Widget*> widgetsMap;
  std::vector<UI::Widget*> widgets;
  
  std::vector<std::pair<std::string, UI::Widget*>> widgetsToAdd;

  Shader* shader = nullptr;
  Spritebatch* spritebatch = nullptr;
public:
    HERO UserInterface(const Sid& sid, const Sid& windowSid, 
      const Sid& inputSid);
    HERO ~UserInterface();

    HERO void init();
    HERO void update();
    HERO void close();

    HERO bool add(const std::string& name, UI::Widget* widget);
    HERO bool remove(const std::string& name);
    HERO UI::Widget* get(const std::string& name);
    HERO void Clear();

    HERO void setShader(Shader* _shader);
};

}
}