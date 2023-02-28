#pragma once

namespace Hero
{

class ICloneable
{
public:
    virtual class ICloneable* Clone() = 0;
};

}