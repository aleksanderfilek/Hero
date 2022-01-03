#include"Texture.hpp"
#include"Font.hpp"
#include"Color.hpp"

#include<iostream>
#include<cstdlib>

namespace Hero
{

Texture::Texture(const char* _path, uint8_t _flags = 
    (uint8_t)TextureFlag::LINEAR | (uint8_t)TextureFlag::NO_MIPMAP)
{
    // load texture from file
    int width, height;
    unsigned char *image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);

    if(!image)
    {
        std::cout<<"Could not load texture: "<< path<<std::endl;
        exit(-1);
    }

    unsigned int gl_id;
    glGenTextures(1, &gl_id);
    DEBUG_CODE( glCheckError(); )
    glBindTexture(GL_TEXTURE_2D, gl_id);
    DEBUG_CODE( glCheckError(); )
    
    int param = (textureFlags & 1)?GL_LINEAR: GL_NEAREST;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
    DEBUG_CODE( glCheckError(); )

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    DEBUG_CODE( glCheckError(); )

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, 
        GL_RGBA, GL_UNSIGNED_BYTE, image);
    DEBUG_CODE( glCheckError(); )

    if(flags & 2){
        glGenerateMipmap(GL_TEXTURE_2D);
        DEBUG_CODE( glCheckError(); )
    }

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    DEBUG_CODE( glCheckError(); )

    glId = gl_id;
    size = (Int2){ width, height };
    name = path;
    flags = flags;
}

Texture::Texture(const char* _name, uint32_t _glId, Int2 _size, uint8_t _flags)
    : name(_name), glId(_glId), size(_size), flags(_flags)
{}

Texture::Texture(const char* text, const ColorRGB& color, 
    const Font& font, uint8_t flags)
{
    
}

Texture::~Texture()
{
    glDeleteTextures(1, &glId);
    DEBUG_CODE( glCheckError(); )
}

void Texture::bind()
{
    glActiveTexture(GL_TEXTURE0);
    DEBUG_CODE( glCheckError(); )
    glBindTexture(GL_TEXTURE_2D, texture->glId);
    DEBUG_CODE( glCheckError(); )
}

void Texture::unbind()
{
    glDisable(GL_TEXTURE_2D);
    DEBUG_CODE( glCheckError(); )
}

}