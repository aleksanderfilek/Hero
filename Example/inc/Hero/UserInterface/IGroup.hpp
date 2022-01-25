#pragma once

#include"IElement.hpp"
#include"Math.hpp"

#include<map>
#include<string>

namespace Hero
{
namespace UI
{

class IGroup : public IElement
{
protected:
  std::map<std::string, IElement*> children;
  
  Int4 rect;
public:
  HERO virtual ~IGroup();

  HERO virtual bool add(const std::string& name, IElement* element) = 0;
  HERO virtual bool remove(const std::string& name) = 0;

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