#pragma once

#include"../Core/Math.hpp"
#include"../Systems/Resources.hpp"
#include "../Graphics/Color.hpp"

namespace Hero
{
    class Font;

    enum class TextureFlag : uint8_t
    {
        NEAREST = 0,
        LINEAR = 1,
        NO_MIPMAP = 0,
        MIPMAP =  2       
    };

    class Texture : public ResourceHandle
    {
        private:
            uint32_t glId;
            Int2 size;
            uint8_t flags;
            ColorChannel channels; 
            ColorSpace colorSpace;

        public:
            HERO Texture();
            HERO Texture(uint32_t _glId, Int2 _size, uint8_t _flags, ColorChannel _channels, ColorSpace _colorSpace);
            HERO Texture(const std::string& text, const ColorRGB& color, const Font* font, uint8_t _flags);
            HERO ~Texture();

            HERO static ResourceHandle* Load(uint8_t* Data, Resources* system);
            HERO static void Unload(ResourceHandle* resource);
            static int GetId(){ return TEXTURE_ID; }

            HERO void bind();
            HERO void unbind();

            inline uint32_t getGlId() const { return glId; }
            inline Int2 getSize() { return size; }
    };
} // namespace Hero