#pragma once

#include "../Definitions.h"
#include "../Math/Float4.h"
#include <cstdint>

struct HERO_API Color
{
    uint8_t R, G, B, A;

	Color():R(255), G(255), B(255), A(255){}
	Color(uint8_t R, uint8_t G, uint8_t B, uint8_t A = 255):
		R(R), G(G), B(B), A(A){}

	Float4 ToFloat4() const;
};

#define COLOR_WHITE { 0xFF, 0xFF, 0xFF, 0xFF }
#define COLOR_BLACK { 0x00, 0x00, 0x00, 0xFF }

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
