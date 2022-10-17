#pragma once

namespace Hero
{

class ISerializable
{
public:
    virtual uint32_t Serialize(uint8_t*& bytes) = 0;
    virtual void Deserialize(uint8_t* bytes, uint32_t size) = 0;
};

}