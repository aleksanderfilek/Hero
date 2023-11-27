#pragma once

namespace Hero
{

class ICloneable
{
public:
    virtual class Actor* Clone() = 0;
};

}