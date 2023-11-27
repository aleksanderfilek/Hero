#pragma once

#include"../ThirdParty/SDL2/SDL_ttf.h"
#include"../Systems/Resources.hpp"

#include<cstdint>

/*
file format
resourceId
fontSize
pathSize
pathString
*/

namespace Hero
{

class Font : ResourceHandle
{
    private:
        uint32_t size;
        TTF_Font* ttfFont;

    public:
        HERO Font();
        HERO ~Font();

        HERO static ResourceHandle* Load(uint8_t* Data, Resources* system);
        HERO static void Unload(ResourceHandle* resource);
        static int GetId(){ return FONT_ID; }

        inline TTF_Font* getTTFFont() const { return ttfFont; }
        inline uint32_t GetSize() const { return size; }
};
} // namespace Hero
