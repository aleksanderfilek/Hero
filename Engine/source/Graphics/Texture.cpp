#include"Texture.hpp"
#include"Font.hpp"
#include"Color.hpp"
#include"../Core/Debug.hpp"
#include"../Utility/Qoi.hpp"
#include"../Utility/ByteOperations.hpp"

#include<iostream>
#include<cstdlib>

namespace Hero
{

HERO Texture::Texture()
{}

HERO Texture::Texture(uint32_t width, uint32_t height, ColorChannel channel)
{
    uint32_t texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int format = ConvertColorChannelToGl(channel);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  

    glId = texture;
    size = {(int)width, (int)height};
    flags = (uint8_t)TextureFlag::NEAREST | (uint8_t)TextureFlag::NO_MIPMAP; 
    channels = channel;
    colorSpace = ColorSpace::Linear;
}

HERO Texture::Texture(uint32_t _glId, Int2 _size, uint8_t _flags, ColorChannel _channels, ColorSpace _colorSpace)
    : glId(_glId), size(_size), flags(_flags), channels(_channels), colorSpace(_colorSpace)
{}

HERO Texture::Texture(const std::string& text, const ColorRGB& color, 
    const Font* font, uint8_t _flags)
{
    SDL_Surface* surface = TTF_RenderText_Blended( font->getTTFFont(), text.c_str(), color.convertToSDLColor() );
    if( !surface)
    {
        std::cout<<"Unable to render text surface! SDL_ttf Error: "<<TTF_GetError()<<std::endl;
        return;
    }

    int mode = GL_RED;
    if(surface->format->BytesPerPixel == 3)
        mode = GL_RGB;
    else if(surface->format->BytesPerPixel == 4)
        mode = GL_RGBA;

    unsigned int gl_id;
    glGenTextures(1, &gl_id);
    glCheckError();
    glBindTexture(GL_TEXTURE_2D, gl_id);
    glCheckError();
    int param = (_flags & 1)?GL_LINEAR: GL_NEAREST;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0,
                            GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    glCheckError();

    if(_flags & 128){
        glGenerateMipmap(GL_TEXTURE_2D);
        glCheckError();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glCheckError();

    glId = gl_id;
    size = (Int2){ surface->w, surface->h };
    flags = _flags;

    SDL_FreeSurface(surface);
}

HERO Texture::~Texture()
{
    glDeleteTextures(1, &glId);
    glCheckError();
}

HERO void Texture::bind()
{
    glActiveTexture(GL_TEXTURE0);
    glCheckError();
    glBindTexture(GL_TEXTURE_2D, glId);
    glCheckError();
}

HERO void Texture::unbind()
{
    glDisable(GL_TEXTURE_2D);
    glCheckError();
}

HERO ResourceHandle* Texture::Load(uint8_t* Data, Resources* system)
{
    int index = 0;

    int width = ReadUint32(Data, &index);
    int height = ReadUint32(Data, &index);
    uint8_t channels = ReadUint8(Data, &index);
    uint8_t colorSpace = ReadUint8(Data, &index);
    uint8_t flags = ReadUint8(Data, &index);;
    uint32_t ByteLength = ReadUint32(Data, &index);

    uint8_t* imgData = new  uint8_t[ByteLength];
    ReadPtr(Data, &index, imgData, ByteLength);

    uint8_t* image = QOI::Decode(imgData, ByteLength, width, height, channels);

    delete[] imgData;

    unsigned int gl_id;
    glGenTextures(1, &gl_id);
    glCheckError();
    glBindTexture(GL_TEXTURE_2D, gl_id);
    glCheckError();
    
    int param = (flags & 1)?GL_LINEAR: GL_NEAREST;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
    glCheckError();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glCheckError();

    int glChannel = ConvertColorChannelToGl(ConvertToColorChannel(channels));
    glTexImage2D(GL_TEXTURE_2D, 0, glChannel, width, height, 0, 
        glChannel, GL_UNSIGNED_BYTE, image);
    glCheckError();

    if(flags & 2){
        glGenerateMipmap(GL_TEXTURE_2D);
        glCheckError();
    }

    delete[] image;
    glBindTexture(GL_TEXTURE_2D, 0);
    glCheckError();
    std::cout<<"ok"<<std::endl;

    Texture* texture = new Texture();

    texture->glId = gl_id;
    texture->size = (Int2){ width, height };
    texture->flags = flags;
    texture->channels = (channels == 3)?ColorChannel::RGB : ColorChannel::RGBA;
    texture->colorSpace = (colorSpace == 0)?ColorSpace::SRGB : ColorSpace::Linear;    std::cout<<"ok"<<std::endl;

    return texture;
}

HERO void Texture::Unload(ResourceHandle* resource)
{
    delete resource;
}

}