#pragma once

#include "../Definitions.h"
#include "ResourceHandle.h"
#include "../GenericTypes/String.h"

class HERO_API Font : public ResourceHandle
{
private:
    struct stbtt_fontinfo* info;
    uint8_t* buffer;

public:
    Font(struct stbtt_fontinfo* Info, uint8_t* Buffer);
    ~Font();

    class Texture* CreateTexture(const String& Text, uint32_t Height);
    int GetTextWidth(const String& Text, uint32_t Height) const;
};