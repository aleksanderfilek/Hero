#include "TextureLoader.h"
#include "../../../Resources/Texture.h"
#include "../../../ThirdParty/GL/Gl.h"
#include "../../../Utility/ByteOperations.h"
#include "../../../Utility/QOI.h"

ResourceHandle* TextureLoader::Load(const uint8_t* Data, class ResourceSubsystem* Subsystem)
{
    int index = 0;

    uint32_t width =            ByteOperations::ReadUint32(Data, &index);
    uint32_t height =           ByteOperations::ReadUint32(Data, &index);
    uint8_t channel =           ByteOperations::ReadUint8(Data, &index);
    uint8_t colorSpace =        ByteOperations::ReadUint8(Data, &index);
    uint8_t filter =            ByteOperations::ReadUint8(Data, &index);
    uint8_t wrap =              ByteOperations::ReadUint8(Data, &index);
    uint8_t generateMipmap =    ByteOperations::ReadUint8(Data, &index);
    uint32_t atlasWidth =       ByteOperations::ReadUint32(Data, &index);
    uint32_t atlasHeigh =       ByteOperations::ReadUint32(Data, &index);
    uint32_t ByteLength =       ByteOperations::ReadUint32(Data, &index);

    uint8_t* imageBuffer = new  uint8_t[ByteLength];
    ByteOperations::ReadPtr(Data, &index, imageBuffer, ByteLength);
    uint8_t* pixels = QOI::Decode(imageBuffer, ByteLength, width, height, channel);
    delete[] imageBuffer;

    TextureConfiguration configuration = {
        .Size =             { (int)width, (int)height },
        .Channels =         (ColorChannel)channel, 
        .ColorSpace =       (ColorSpace)colorSpace,
        .FilterMethod =     (TextureFilterMethod)filter,
        .WrapMethod =       (TextureWrapMethod)wrap,
        .GenerateMipmaps =  generateMipmap > 0,
        .AtlasSize =        { (int)atlasWidth, (int)atlasHeigh }
    };

    Texture* texture = new Texture(pixels, configuration);

    delete[] pixels;

    return texture;
}

void TextureLoader::Unload(ResourceHandle* Resource)
{
    delete Resource;
}