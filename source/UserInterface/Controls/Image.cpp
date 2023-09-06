#include "Image.h"
#include "../../Graphics/MultiTextureSpritebatch.h"
#include <iostream>

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
    //std::cout<<GetAbsolutePosition()<<" / "<<GetAbsoluteSize()<<"\n";
    // Spritebatch->DrawTexture(texture, GetAbsolutePosition(),
    //     GetAbsoluteSize(), textureRect, color);
}