#include "Texture.h"
#include "../Utility/ByteOperations.h"
#include "../ThirdParty/GL/Gl.h"

#include<iostream>
#include<cstdlib>

static int ConvertFilterToGL(TextureFilterMethod Method);
static int ConvertWraplToGl(TextureWrapMethod Method);
static int ConvertColorChannelToGl(ColorChannel Channel);

Texture::Texture()
{}

Texture::Texture(const uint8_t* Pixels, const TextureConfiguration& Coniguration)
    :configuration(Coniguration)
{
    glGenTextures(1, &glId);
    glBindTexture(GL_TEXTURE_2D, glId);

    int glFilter = ConvertFilterToGL(configuration.FilterMethod);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glFilter);
    GlCheckError();

    int glWrap = ConvertWraplToGl(configuration.WrapMethod);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrap);
    GlCheckError();

    int glChannel = ConvertColorChannelToGl(configuration.Channels);
    glTexImage2D(GL_TEXTURE_2D, 0, glChannel, configuration.Size.X, 
        configuration.Size.Y, 0, glChannel, GL_UNSIGNED_BYTE, Pixels);

    if (configuration.GenerateMipmaps) 
    {
        glGenerateMipmap(GL_TEXTURE_2D);
        GlCheckError();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    GlCheckError();
}

Texture::Texture(uint32_t GlId, const TextureConfiguration& Coniguration)
    : glId(GlId), configuration(Coniguration)
{
    
}

Texture::~Texture()
{
    glDeleteTextures(1, &glId);
    GlCheckError();
}

void Texture::Bind(int SlotId)
{
    glActiveTexture(GL_TEXTURE0 + SlotId);
    GlCheckError();
    glBindTexture(GL_TEXTURE_2D, glId);
    GlCheckError();
}

void Texture::Unbind()
{
    glDisable(GL_TEXTURE_2D);
    GlCheckError();
}

void Texture::SetAtlasSize(const Int2& AtlasSize)
{
    configuration.AtlasSize = AtlasSize;
}

Float4 Texture::GetSpriteRect(int Index)
{
    int horizontalSpriteCount = configuration.Size.X / configuration.AtlasSize.X;
    int verticalSpriteCount = configuration.Size.Y / configuration.AtlasSize.Y;

    int xCoord = Index % horizontalSpriteCount;
    int yCoord = Index / horizontalSpriteCount;

    Float4 result;
    result.Z = 1.0f / (horizontalSpriteCount + 1);
    result.W = 1.0f / (verticalSpriteCount + 1);
    result.X = result.Z * xCoord;
    result.Y = result.W * yCoord;

    return result;
}

int ConvertFilterToGL(TextureFilterMethod Method)
{
    int gl = 0;

    switch (Method)
    {
    case TextureFilterMethod::NEAREST:
        gl = GL_NEAREST;
        break;
    case TextureFilterMethod::LINEAR:
        gl = GL_LINEAR;
        break;
    }

    return gl;
}

int ConvertWraplToGl(TextureWrapMethod Method)
{
    int gl = 0;

    switch (Method)
    {
    case TextureWrapMethod::REPEAT:
        gl = GL_REPEAT;
        break;
    case TextureWrapMethod::CLAMP_TO_EDGE:
        gl = GL_CLAMP_TO_EDGE;
        break;
    case TextureWrapMethod::CLAMP_TO_BORDER:
        gl = GL_CLAMP_TO_BORDER;
        break;
    case TextureWrapMethod::MIRRORED_REPEAT:
        gl = GL_MIRRORED_REPEAT;
        break;
    case TextureWrapMethod::MIRROR_CLAMP_TO_EDGE:
        gl = GL_MIRROR_CLAMP_TO_EDGE;
        break;
    }

    return gl;
}

int ConvertColorChannelToGl(ColorChannel Channel)
{
    int gl = 0;

    switch (Channel)
    {
    case ColorChannel::RED:
        gl = GL_RED;
        break;
    case ColorChannel::RGB:
        gl = GL_RGB;
        break;
    case ColorChannel::RGBA:
        gl = GL_RGBA;
        break;
    }

    return gl;
}