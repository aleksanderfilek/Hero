#pragma once

#include"Math.hpp"
#include"IResource.hpp"

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
            HERO Texture();
            HERO Texture(const char* _name, uint32_t _glId, Int2 _size, uint8_t _flags);
            HERO Texture(const char* text, const ColorRGB& color, const Font* font, uint8_t _flags);
            HERO ~Texture();

            HERO static IResource* Load(const std::string& path);
            HERO static void Unload(IResource* resource);
            static int GetId(){ return 3; }

            HERO void bind();
            HERO void unbind();

            inline uint32_t getGlId() const { return glId; }
            inline Int2 getSize() { return size; }
            inline const char* getName() const { return name; }
    };
} // namespace Hero