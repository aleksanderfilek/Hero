// #include "Texture.h"
// #include "../Core/Debug.h"
// #include "../Utilities/Qoi.h"
// #include "../Utilities/ByteOperations.h"
// #include "../ThirdParty/GL/Gl.h"

// #include<iostream>
// #include<cstdlib>

// Texture::Texture()
// {}

// Texture::Texture(uint32_t width, uint32_t height, ColorChannel channel)
// {
//     uint32_t texture;
//     glGenTextures(1, &texture);
//     glBindTexture(GL_TEXTURE_2D, texture);

//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glCheckError();

//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//     glCheckError();

//     int format = convertColorChannelToGl(channel);
//     glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);

//     glBindTexture(GL_TEXTURE_2D, 0);
//     glCheckError();

//     mGlId = texture;
//     mSize = { (int)width, (int)height };
//     mFlags = (uint8_t)TextureFlag::NEAREST | (uint8_t)TextureFlag::NO_MIPMAP;
//     mChannels = channel;
//     mColorSpace = ColorSpace::LINEAR;
//     mAtlasSize = { (int)width, (int)height };
// }

// Texture::Texture(uint32_t glId, Int2 size, uint8_t flags, ColorChannel channels, ColorSpace colorSpace)
//     : mGlId(glId), mSize(size), mFlags(flags), mChannels(channels), mColorSpace(colorSpace)
// {
//     mAtlasSize = size;
// }

// Texture::~Texture()
// {
//     glDeleteTextures(1, &mGlId);
//     glCheckError();
// }

// void Texture::bind(int slotId)
// {
//     glActiveTexture(GL_TEXTURE0 + slotId);
//     glCheckError();
//     glBindTexture(GL_TEXTURE_2D, mGlId);
//     glCheckError();
// }

// void Texture::unbind()
// {
//     glDisable(GL_TEXTURE_2D);
//     glCheckError();
// }

// ResourceHandle* Texture::load(const uint8_t* Data, ResourceSubsystem* subsystem)
// {
//     int index = 0;

//     int width = readUint32(Data, &index);
//     int height = readUint32(Data, &index);
//     uint8_t channels = readUint8(Data, &index);
//     uint8_t colorSpace = readUint8(Data, &index);
//     uint8_t flags = readUint8(Data, &index);
//     uint32_t atlasWidth = readUint32(Data, &index);
//     uint32_t atlasHeigh = readUint32(Data, &index);
//     uint32_t ByteLength = readUint32(Data, &index);

//     uint8_t* imgData = new  uint8_t[ByteLength];
//     readPtr(Data, &index, imgData, ByteLength);
//     uint8_t* image = QOI::decode(imgData, ByteLength, width, height, channels);
//     delete[] imgData;

//     unsigned int gl_id;
//     glGenTextures(1, &gl_id);
//     glCheckError();
//     glBindTexture(GL_TEXTURE_2D, gl_id);
//     glCheckError();

//     int param = (flags & 1) ? GL_LINEAR : GL_NEAREST;
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
//     glCheckError();

//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//     glCheckError();

//     int glChannel = convertColorChannelToGl(convertToColorChannel(channels));
//     glTexImage2D(GL_TEXTURE_2D, 0, glChannel, width, height, 0,
//         glChannel, GL_UNSIGNED_BYTE, image);
//     glCheckError();

//     if (flags & 2) {
//         glGenerateMipmap(GL_TEXTURE_2D);
//         glCheckError();
//     }

//     delete[] image;
//     glBindTexture(GL_TEXTURE_2D, 0);
//     glCheckError();

//     Texture* texture = new Texture();

//     texture->mGlId = gl_id;
//     texture->mSize = { width, height };
//     texture->mFlags = flags;
//     texture->mChannels = (channels == 3) ? ColorChannel::RGB : ColorChannel::RGBA;
//     texture->mColorSpace = (colorSpace == 0) ? ColorSpace::SRGB : ColorSpace::LINEAR;
//     texture->setAtlasSize(Int2(atlasWidth, atlasHeigh));
//     return texture;
// }

// void Texture::unload(ResourceHandle* resource)
// {
//     delete resource;
// }

// void Texture::setAtlasSize(const Int2& AtlasSize)
// {
//     mAtlasSize = AtlasSize;
// }

// Float4 Texture::getSpriteRect(int index)
// {
//     int horizontalSpriteCount = mSize.x / mAtlasSize.x;
//     int verticalSpriteCount = mSize.y / mAtlasSize.y;

//     int xCoord = index % horizontalSpriteCount;
//     int yCoord = index / horizontalSpriteCount;

//     Float4 result;
//     result.z = 1.0f / (horizontalSpriteCount + 1);
//     result.w = 1.0f / (verticalSpriteCount + 1);
//     result.x = result.z * xCoord;
//     result.y = result.w * yCoord;

//     return result;
// }