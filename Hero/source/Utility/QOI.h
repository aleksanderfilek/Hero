#pragma once

#include "../Definitions.h"
#include <cstdint>

class HERO_API QOI
{
public:
	static uint8_t* Encode(uint8_t* Data, uint32_t Width, uint32_t Height, uint8_t Channels, uint32_t& ByteLength);
	static uint8_t* Decode(uint8_t* Data, uint32_t Size, int Width, int Height, uint8_t Channels);
};