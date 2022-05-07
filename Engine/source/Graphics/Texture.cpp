#include"Texture.hpp"
#include"Font.hpp"
#include"Color.hpp"
#include"../Core/Debug.hpp"
#include"../Utility/Qoi.hpp"

#include<iostream>
#include<cstdlib>
#include<fstream>


namespace Hero
{

HERO Texture::Texture()
{}

HERO Texture::Texture(const std::string& _name, uint32_t _glId, Int2 _size, uint8_t _flags, ColorChannel _channels, ColorSpace _colorSpace)
    : name(_name), glId(_glId), size(_size), flags(_flags), channels(_channels), colorSpace(_colorSpace)
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

    int mode = GL_RGB;
    if(surface->format->BytesPerPixel == 4)
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
    name = text;
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

HERO IResource* Texture::Load(const std::string& path)
{
    // load texture from file

    std::ifstream file(path, std::ios::binary);

    if(!file.is_open())
    {
        std::cout<<"Could not open asset: "<< path<<std::endl;
        exit(-1);
        return nullptr;
    }

    int ResourceId;
    file.read((char*)&ResourceId, sizeof(int));
    int width, height;
    file.read((char*)&width, sizeof(int));
    file.read((char*)&height, sizeof(int));
    uint8_t channels;
    file.read((char*)&channels, sizeof(uint8_t));
    uint8_t colorSpace;
    file.read((char*)&colorSpace, sizeof(uint8_t));
    uint8_t flags;
    file.read((char*)&flags, sizeof(uint8_t));
    uint32_t ByteLength;
    file.read((char*)&ByteLength, sizeof(uint32_t));
    uint8_t* Data = new  uint8_t[ByteLength];
    file.read((char*)Data, ByteLength*sizeof(char));

    file.close();

    uint8_t* image = QOI::Decode(Data, ByteLength, width, height, channels);

    delete[] Data;

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

    uint32_t glChannel = (channels == 3)? GL_RGB : GL_RGBA;
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

    Texture* texture = new Texture();

    texture->glId = gl_id;
    texture->size = (Int2){ width, height };
    texture->name = path;
    texture->flags = flags;
    texture->channels = (channels == 3)?ColorChannel::RGB : ColorChannel::RGBA;
    texture->colorSpace = (colorSpace == 0)?ColorSpace::SRGB : ColorSpace::Linear;
    return texture;
}

HERO void Texture::Unload(IResource* resource)
{

}

}