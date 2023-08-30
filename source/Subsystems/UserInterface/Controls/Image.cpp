#include "Image.h"
#include "../../../Graphics/MultiTextureSpritebatch.h"

void Image::SetTexture(class Texture* Texture)
{
    texture = texture;
}

void Image::SetTextureRect(const Float4& TextureRect)
{
    textureRect = TextureRect;
}

void Image::SetColor(const Color& Color)
{
    color = color;
}

void Image::Draw(class MultiTextureSpritebatch* Spritebatch)
{
    Spritebatch->DrawTexture(texture, GetAbsolutePosition(),
        GetAbsoluteSize(), textureRect, color);
}