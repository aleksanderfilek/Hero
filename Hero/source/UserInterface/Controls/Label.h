#pragma once

#include "Image.h"

enum class TextAlligment
{
    LEFT_TOP,
    TOP,
    RIGHT_TOP,
    LEFT,
    CENTER,
    RIGHT,
    LEFT_BOTTOM,
    BOTTOM,
    RIGHT_BOTTOM,
};

struct LabelStyle
{
    class Font* Font = nullptr;
    TextAlligment Alligment = TextAlligment::LEFT;
    uint32_t Size = 24;
    Color Color;
};

class HERO_API Label : public Image
{
private:
    String text;
    Int2 textureSize;
    Int2 texturePosition;
    TextAlligment alligment = TextAlligment::LEFT_TOP;
    class Font* font = nullptr;
    uint32_t textSize = 24;

    void CalculateAlligment();

public:
    ~Label();

    void SetAlligment(TextAlligment Alligment);
    void SetFont(class Font* Font);
    class Font* GetFont() const { return font; }
    void SetText(const String& Text);
    String GetText() const { return text; }
    void SetTextSize(uint32_t Size);
    uint32_t GeTextSize() const { return textSize; }
    void Apply();

    virtual void Draw(class ISpriteRenderer* SpriteRenderer) override;
    virtual void _InternalUpdateTransforms() override;

public:
    void SetLabelStyle(LabelStyle& Style);
    LabelStyle GetLabelStyle() const;
};