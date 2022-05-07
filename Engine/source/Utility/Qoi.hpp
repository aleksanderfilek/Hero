#pragma once

#include<cstdint>

#include "../Graphics/Color.hpp"

namespace Hero
{

namespace QOI
{

HERO uint8_t* Encode(uint8_t* Data, uint32_t Width, uint32_t Height, uint8_t Channels, uint32_t& ByteLength);
HERO uint8_t* Decode(uint8_t* Data, uint32_t Size, int Width, int Height, uint8_t Channels);

}
  
}