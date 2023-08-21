#pragma once

#include "../Definitions.h"
#include "../Math/Int2.h"
#include "../Math/Float4.h"
#include "../Graphics/Color.h"
#include "ResourceHandle.h"

#include <cstdint>

enum class TextureFilterMethod : uint8_t
{
    NEAREST =   0,
    LINEAR =    1
};

enum class TextureWrapMethod : uint8_t
{
    REPEAT =                0,
    CLAMP_TO_EDGE =         1,
    CLAMP_TO_BORDER =       2,
    MIRRORED_REPEAT =       3,
    MIRROR_CLAMP_TO_EDGE =  4
};

struct TextureConfiguration
{
    Int2 Size;
    ColorChannel Channels;
    ColorSpace ColorSpace;
    TextureFilterMethod FilterMethod;
    TextureWrapMethod WrapMethod;
    bool GenerateMipmaps = false;
    Int2 AtlasSize;
};

class HERO_API Texture : public ResourceHandle
{
private:
    uint32_t glId = 0;
    TextureConfiguration configuration;

public:
    Texture();
    Texture(const uint8_t* Pixels, const TextureConfiguration& Coniguration);
    Texture(uint32_t GlId, const TextureConfiguration& Coniguration);
    ~Texture();

    void Bind(int SlotId = 0);
    void Unbind();

    uint32_t GetGlId() const { return glId; }
    Int2 GetSize() const { return configuration.Size; }
    TextureFilterMethod GetFilterMethod() const { return configuration.FilterMethod; }
    TextureWrapMethod GetWrapMethod() const { return configuration.WrapMethod; }
    ColorChannel GetColorChannel() const { return configuration.Channels; }
    ColorSpace GetColorSpace() const { return configuration.ColorSpace; }
    bool GetGenerateMipmap() const { return configuration.GenerateMipmaps; }

    void SetAtlasSize(const Int2& AtlasSize);
    Int2 GetAtlasSize() const { return configuration.AtlasSize; }
    Float4 GetSpriteRect(int Index);
};