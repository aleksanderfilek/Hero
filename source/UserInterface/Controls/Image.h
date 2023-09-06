#pragma once

#include "Control.h"
#include "../../Graphics/Color.h"
#include "../../Math/Float4.h"

class HERO_API Image : public Control
{
protected:
    class Texture* texture = nullptr;
    Float4 textureRect = Float4(0.0f, 0.0f, 1.0f, 1.0f);
    Color color;

public:
    void SetTexture(class Texture* Texture);
    void SetTextureRect(const Float4& TextureRect);
    void SetColor(const Color& Color);

    virtual void Draw(class MultiTextureSpritebatch* Spritebatch) override;
};