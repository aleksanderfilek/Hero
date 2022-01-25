#include"IGroup.hpp"

namespace Hero
{
namespace UI
{

HERO IGroup::~IGroup()
{
  for(auto& child: children)
  {
    delete child.second;
  }
}

}
}