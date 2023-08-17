#pragma once

#include "../Definitions.h"
#include <cstdint>

struct HERO_API Color
{
    uint8_t R, G, B, A;

	Color():R(0), G(0), B(0), A(255){}
	Color(uint8_t R, uint8_t G, uint8_t B, uint8_t A = 255):
		R(R), G(G), B(B), A(A){}
};

enum class ColorSpace : uint8_t
{
	SRGB = 0,
	LINEAR = 1
};

enum class ColorChannel : uint8_t
{
	RED = 1,
	RGB = 3,
	RGBA = 4
};
