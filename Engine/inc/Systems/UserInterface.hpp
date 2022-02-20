#pragma once

#include"ISystem.hpp"
#include"Widget.hpp"
#include"Spritebatch.hpp"

#include<map>
#include<string>

namespace Hero
{
namespace System
{ 

class Window;
class Input;

class UserInterface : public ISystem
{
private:
  Window* window = nullptr;
  Input* input = nullptr;

  std::map<std::string, UI::Widget*> widgets;

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

    HERO void setShader(Shader* _shader);
};

}
}