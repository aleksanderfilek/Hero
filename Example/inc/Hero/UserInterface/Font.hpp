#pragma once

#include"ThirdParty.hpp"
#include<cstdint>

namespace Hero
{

    class Font
    {
        private:
            const char* name;
            uint32_t size;
            TTF_Font* font;

        public:
            Font(const char* _path, uint32_t _size);
            ~Font();

            inline TTF_Font* getTTFFont(){ return font; }
    };
} // namespace Hero
