// #pragma once

// #include "../Defaults.h"
// #include "ResourceSubsystem.h"
// #include "../Core/Math.h"
// #include "../Graphics/Color.h"

// #include <cstdint>

// enum class TextureFlag : uint8_t
// {
//     NEAREST = 0,
//     LINEAR = 1,
//     NO_MIPMAP = 0,
//     MIPMAP = 2
// };

// class HERO_API Texture : public ResourceHandle
// {
// private:
//     uint32_t mGlId;
//     Int2 mSize;
//     uint8_t mFlags;
//     ColorChannel mChannels;
//     ColorSpace mColorSpace;
//     Int2 mAtlasSize;

// protected:
//     friend void setGlIdValue(Texture* texture, uint32_t value)
//     {
//         texture->mGlId = value;
//     }

//     friend void setFlagValue(Texture* texture, uint8_t value)
//     {
//         texture->mFlags = value;
//     }

//     friend void setColorChannelValue(Texture* texture, ColorChannel value)
//     {
//         texture->mChannels = value;
//     }

//     friend void setColorChannelValue(Texture* texture, ColorSpace value)
//     {
//         texture->mColorSpace = value;
//     }

//     friend void setAtlasSizeValue(Texture* texture, Int2 value)
//     {
//         texture->mAtlasSize = value;
//     }

// public:
//     Texture();
//     Texture(uint32_t width, uint32_t height, ColorChannel channel);
//     Texture(uint32_t glId, Int2 size, uint8_t flags, ColorChannel channel, ColorSpace colorSpace);
//     ~Texture();

//     static ResourceHandle* load(const uint8_t* Data, ResourceSubsystem* subsystem);
//     static void unload(ResourceHandle* resource);
//     static int getId() { return TEXTURE_ID; }

//     void bind(int slotId = 0);
//     void unbind();

//     inline uint32_t getGlId() const { return mGlId; }
//     inline Int2 getSize() const { return mSize; }
//     inline uint8_t getFlags() const { return mFlags; }
//     inline ColorChannel getColorChannel() const { return mChannels; }
//     inline ColorSpace getColorSpace() const { return mColorSpace; }

//     void setAtlasSize(const Int2& AtlasSize);
//     Int2 getAtlasSize() const { return mAtlasSize; }
//     Float4 getSpriteRect(int index);
// };