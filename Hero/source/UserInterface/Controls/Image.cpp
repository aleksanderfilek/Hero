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

    if (GetVisibility() == VisibilityState::HIDDEN)
        return;

    SpriteRenderer->DrawTextureEx(texture, GetAbsolutePosition(),
        GetAbsoluteSize(), textureRect, color);
}

void Image::SetImageStyle(const ImageStyle& Style)
{
    texture = Style.Texture;
    textureRect = Style.Rect;
    color = Style.Color;
}

ImageStyle Image::GetImageStyle() const
{
    return { texture, textureRect, color };
}