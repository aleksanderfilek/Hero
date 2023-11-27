#pragma once

#include"IElement.hpp"
#include"../Core/Math.hpp"

#include<map>
#include<string>

namespace Hero
{
namespace UI
{

class HERO IGroup : public IElement
{
  friend class IElement;
protected:
  std::map<std::string, IElement*> children;
  
  Int4 rect;

  bool lastTick = true;

public:
  HERO virtual ~IGroup();

  HERO void update(Int2 mousePosition, uint8_t buttonState) override;
  HERO void draw(Spritebatch* spritebatch) override;
  HERO virtual bool add(const std::string& name, IElement* element);
  HERO virtual bool remove(const std::string& name);

  template<class T>
  T* get(const std::string& path)
  {
    size_t namePos = path.find("/");
    auto it = children.find(path.substr(0, namePos));
    if(it == children.end())
    {
      return nullptr;
    }

    return ((IGroup*)it->second)->get<T>(path.substr(namePos+1));
  }

  inline uint32_t getChildrenCount(){ return children.size(); }
};

}
}