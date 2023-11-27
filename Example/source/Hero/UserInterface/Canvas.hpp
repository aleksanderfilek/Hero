#pragma once

#include"IGroup.hpp"

namespace Hero
{
namespace UI
{

class HERO Canvas : public IGroup
{
public:
  HERO bool add(const std::string& name, IElement* element) override;
};

}
}