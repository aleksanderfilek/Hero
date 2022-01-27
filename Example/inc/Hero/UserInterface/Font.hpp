#pragma once

#include"ThirdParty.hpp"
#include<cstdint>

namespace Hero
{

class HERO Font
{
    private:
        const char* name;
        uint32_t size;
        TTF_Font* font;

    public:
        HERO Font(const char* _path, uint32_t _size);
        HERO ~Font();

        inline TTF_Font* getTTFFont() const { return font; }
};
} // namespace Hero
