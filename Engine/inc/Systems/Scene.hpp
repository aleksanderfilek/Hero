#pragma once 

#include"ISystem.hpp"

namespace Hero
{
namespace System
{

class Actor;
class IComponentSystemHandler;

class HERO Scene : public ISystem
{
public:
    Scene(const Sid& sid);
    ~Scene();

    void init() override;
    void update() override;
    void close() override;
};
  
}
}