#include"Texture.hpp"
#include"Font.hpp"
#include"Color.hpp"
#include"Debug.hpp"

#include<iostream>
#include<cstdlib>

namespace Hero
{

HERO Texture::Texture(const char* _path, uint8_t _flags)
{
    // load texture from file
    int width, height;
    unsigned char *image = SOIL_load_image(_path, &width, &height, 0, SOIL_LOAD_RGBA);

    if(!image)
    {
        std::cout<<"Could not load texture: "<< _path<<std::endl;
        exit(-1);
    }

    unsigned int gl_id;
    glGenTextures(1, &gl_id);
    glCheckError();
    glBindTexture(GL_TEXTURE_2D, gl_id);
    glCheckError();
    
    int param = (_flags & 1)?GL_LINEAR: GL_NEAREST;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
    glCheckError();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glCheckError();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, 
        GL_RGBA, GL_UNSIGNED_BYTE, image);
    glCheckError();

    if(_flags & 2){
        glGenerateMipmap(GL_TEXTURE_2D);
        glCheckError();
    }

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    glCheckError();

    glId = gl_id;
    size = (Int2){ width, height };
    name = _path;
    flags = _flags;
}

HERO Texture::Texture(const char* _name, uint32_t _glId, Int2 _size, uint8_t _flags)
    : name(_name), glId(_glId), size(_size), flags(_flags)
{}

HERO Texture::Texture(const char* text, const ColorRGB& color, 
    const Font* font, uint8_t _flags)
{
    SDL_Surface* surface = TTF_RenderText_Blended( font->getTTFFont(), text, color.convertToSDLColor() );
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

}