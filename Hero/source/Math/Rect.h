#pragma once

#include "../Definitions.h"
#include "Float2.h"

struct HERO_API Rect
{
	Float2 Position;
	Float2 Size;

	Rect(){}
	Rect(const Float2& Position, const Float2& Size) : Position(Position), Size(Size) {}

	constexpr bool Containes(const Rect& Other) const
	{
		return (Other.Position.X >= Position.X) && (Other.Position.X + Other.Size.X < Position.X + Size.X) &&
			(Other.Position.Y >= Position.Y) && (Other.Position.Y + Other.Size.Y < Position.Y + Size.Y);
	}

	constexpr bool Overlaps(const Rect& Other) const
	{
		return Position.X < Other.Position.X + Other.Size.X && Position.X + Size.X >= Other.Position.X &&
			Position.Y < Other.Position.Y + Other.Size.Y && Position.Y + Size.Y >= Other.Position.Y;
	}
};
