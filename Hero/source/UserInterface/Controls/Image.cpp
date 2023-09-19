#include "Image.h"
#include "../../Graphics/SpriteRenderer/ISpriteRenderer.h"

void Image::SetTexture(class Texture* Texture)
{
    texture = Texture;
}

void Image::SetTextureRect(const Float4& TextureRect)
{
    textureRect = TextureRect;
}

void Image::SetColor(const Color& Color)
{
    color = Color;
}

void Image::Draw(class ISpriteRenderer* SpriteRenderer)
{
    if (!texture)
        return;

    SpriteRenderer->DrawTextureEx(texture, GetAbsolutePosition(),
        GetAbsoluteSize(), textureRect, color);
}