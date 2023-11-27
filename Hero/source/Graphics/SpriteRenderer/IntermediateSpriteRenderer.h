#pragma once

#include "ISpriteRenderer.h"
#include "../../GenericTypes/StringId.h"

class HERO_API IntermediateSpriteRenderer : public ISpriteRenderer
{
private:
	class Shader* shader = nullptr;
	void CreateAndRegisterShader();
	class Mesh* mesh = nullptr;
	void CreateAndRegisterPlaneMesh();

public:
	IntermediateSpriteRenderer();
	~IntermediateSpriteRenderer();

	virtual void Start(const Int2& WindowSize) override;
	virtual void End() override;
	virtual void DrawTexture(class Texture* Texture, const Int2& Position, const Int2& Size) override;
	virtual void DrawTextureEx(class Texture* Texture, const Int2& Position, const Int2& Size, const Float4& Rect, Color Color) override;
};