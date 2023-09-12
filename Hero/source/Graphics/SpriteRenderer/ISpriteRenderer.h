#pragma once

#include "../../Definitions.h"
#include "../Color.h"
#include "../../Math/Int2.h"
#include "../../Math/Float4.h"

class HERO_API ISpriteRenderer
{
public:
	virtual ~ISpriteRenderer() {};

	virtual void Start(const Int2& WindowSize) = 0;
	virtual void End() = 0;
	virtual void DrawTexture(class Texture* Texture, const Int2& Position, const Int2& Size) = 0;
	virtual void DrawTextureEx(class Texture* Texture, const Int2& Position, const Int2& Size, const Float4& Rect, Color Color) = 0;
};