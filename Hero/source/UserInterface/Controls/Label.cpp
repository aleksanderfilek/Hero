#include "Label.h"
#include "../../Resources/Texture.h"
#include "../../Resources/Font.h"
#include "../../Graphics/SpriteRenderer/ISpriteRenderer.h"
#include "../../Math/Math.h"

Label::~Label()
{
    if (texture)
    {
        delete texture;
    }
}

void Label::SetAlligment(TextAlligment Alligment)
{
    alligment = Alligment;

    if (texture)
    {
        CalculateAlligment();
    }
}

void Label::SetFont(Font* Font)
{
    font = Font;
}


void Label::SetText(const String& Text)
{
    text = Text;
}

void Label::SetTextSize(uint32_t Size)
{
    textSize = Size;
}

void Label::Apply()
{
    if (!font)
    {
        return;
    }

    if (texture)
    {
        delete texture;
        texture = nullptr;
    }

    if (text.IsEmpty())
    {
        return;
    }

    SetTexture(font->CreateTexture(text, textSize));
    CalculateAlligment();
}

void Label::CalculateAlligment()
{
    Int2 texSize = texture->GetSize();
    Int2 absolutePosition = GetAbsolutePosition();
    Int2 absoluteSize = GetAbsoluteSize();

    switch (alligment)
    {
    case TextAlligment::LEFT_TOP:
        texturePosition = absolutePosition;
        break;
    case TextAlligment::TOP:
        texturePosition.X = absolutePosition.X + (absoluteSize.X - texSize.X) / 2;
        texturePosition.Y = absolutePosition.Y;
        break;
    case TextAlligment::RIGHT_TOP:
        texturePosition.X = absolutePosition.X + absoluteSize.X - texSize.X;
        texturePosition.Y = absolutePosition.Y;
        break;
    case TextAlligment::LEFT:
        texturePosition.X = absolutePosition.X;
        texturePosition.Y = absolutePosition.Y + (absoluteSize.Y - texSize.Y) / 2;
        break;
    case TextAlligment::CENTER:
        texturePosition.X = absolutePosition.X + (absoluteSize.X - texSize.X) / 2;
        texturePosition.Y = absolutePosition.Y + (absoluteSize.Y - texSize.Y) / 2;
        break;
    case TextAlligment::RIGHT:
        texturePosition.X = absolutePosition.X + absoluteSize.X - texSize.X;
        texturePosition.Y = absolutePosition.Y + (absoluteSize.Y - texSize.Y) / 2;
        break;
    case TextAlligment::LEFT_BOTTOM:
        texturePosition.X = absolutePosition.X;
        texturePosition.Y = absolutePosition.Y + absoluteSize.Y - texSize.Y;
        break;
    case TextAlligment::BOTTOM:
        texturePosition.X = absolutePosition.X + (absoluteSize.X - texSize.X) / 2;
        texturePosition.Y = absolutePosition.Y + absoluteSize.Y - texSize.Y;
        break;
    case TextAlligment::RIGHT_BOTTOM:
        texturePosition.X = absolutePosition.X + absoluteSize.X - texSize.X;
        texturePosition.Y = absolutePosition.Y + absoluteSize.Y - texSize.Y;
        break;
    }

    Float4 MinimumArea = {
        (float)max(texturePosition.X, absolutePosition.X),
        (float)max(texturePosition.Y, absolutePosition.Y),
        (float)min(texturePosition.X + texSize.X, absolutePosition.X + absoluteSize.X),
        (float)min(texturePosition.Y + texSize.Y, absolutePosition.Y + absoluteSize.Y) };

    Float4 TranslatedArea = {
        MinimumArea.X - texturePosition.X,
        MinimumArea.Y - texturePosition.Y,
        MinimumArea.Z - texturePosition.X,
        MinimumArea.W - texturePosition.Y };

    Float4 NormalizeArea = {
        TranslatedArea.X / texSize.X,
        TranslatedArea.Y / texSize.Y,
        TranslatedArea.Z / texSize.X,
        TranslatedArea.W / texSize.Y };

    textureRect = NormalizeArea;
    textureSize = { (int)(MinimumArea.Z - MinimumArea.X), (int)(MinimumArea.W - MinimumArea.Y) };
    texturePosition = { (int)MinimumArea.X, (int)MinimumArea.Y };
}

void Label::_InternalUpdateTransforms()
{
    Control::_InternalUpdateTransforms();
    if(texture)
    {
        CalculateAlligment();
    }
}

void Label::Draw(class ISpriteRenderer* SpriteRenderer)
{
    if (!texture) 
        return;

    SpriteRenderer->DrawTextureEx(texture,texturePosition,
        textureSize, textureRect, color);
}

void Label::SetLabelStyle(LabelStyle& Style)
{
    font = Style.Font;
    alligment = Style.Alligment;
    textSize = Style.Size;
    color = Style.Color;
    Apply();
}

LabelStyle Label::GetLabelStyle() const
{
    return { font, alligment, textSize, color };
}