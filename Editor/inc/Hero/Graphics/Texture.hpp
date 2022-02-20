#pragma once

#include"Math.hpp"

namespace Hero
{
    class Font;
    class ColorRGB;

    enum class TextureFlag : uint8_t
    {
        NEAREST = 0,
        LINEAR = 1,
        NO_MIPMAP = 0,
        MIPMAP =  2       
    };

    class Texture
    {
        private:
            const char *name;
            uint32_t glId;
            Int2 size;
            uint8_t flags;

        public:
            HERO Texture(const char* _path, uint8_t _flags = (uint8_t)TextureFlag::LINEAR | (uint8_t)TextureFlag::NO_MIPMAP);
            HERO Texture(const char* _name, uint32_t _glId, Int2 _size, uint8_t _flags);
            HERO Texture(const char* text, const ColorRGB& color, const Font* font, uint8_t _flags);
            HERO ~Texture();

            HERO void bind();
            HERO void unbind();

            inline uint32_t getGlId() const { return glId; }
            inline Int2 getSize() { return size; }
            inline const char* getName() const { return name; }
    };
} // namespace Hero