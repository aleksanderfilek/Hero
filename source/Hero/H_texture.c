#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>

#include"Hero/H_headers.h"
#include"Hero/H_math.h"
#include"Hero/H_color.h"
#include"Hero/H_font.h"
#include"Hero/H_debug.h"

typedef struct
{
    uint32_t glId;
    HeroInt2 size;
    const char *name;
} HeroTexture;

HeroTexture* heroTextureLoad(const char* path, uint8_t textureFlags)
{
    // load texture from file
    int width, height;
    unsigned char *image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);

    if(!image)
    {
        printf("Could not load texture: %s\n", path);
        return NULL;
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

    if(textureFlags & 128){
        glGenerateMipmap(GL_TEXTURE_2D);
        DEBUG_CODE( glCheckError(); )
    }

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    DEBUG_CODE( glCheckError(); )

    HeroTexture* texture = (HeroTexture*)malloc(sizeof(HeroTexture));

    texture->glId = gl_id;
    texture->size = (HeroInt2){ width, height };
    texture->name = path;

    return texture;
}

void heroTextureUnload(HeroTexture* texture)
{
    glDeleteTextures(1, &texture->glId);
    DEBUG_CODE( glCheckError(); )
    free(texture);
}

void heroTextureBind(const HeroTexture* texture)
{
    glActiveTexture(GL_TEXTURE0);
    DEBUG_CODE( glCheckError(); )
    glBindTexture(GL_TEXTURE_2D, texture->glId);
    DEBUG_CODE( glCheckError(); )
}

void heroTextureUnbind()
{
    glDisable(GL_TEXTURE_2D);
    DEBUG_CODE( glCheckError(); )
}

HeroTexture* heroTextureFromText(const char* text, HeroColor* color, HeroFont* font, uint8_t textureFlags)
{
    SDL_Surface* surface = TTF_RenderText_Blended( font, text, *color );
    if( !surface)
    {
            printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
            return NULL;
    }

    int mode = GL_RGB;
    if(surface->format->BytesPerPixel == 4)
            mode = GL_RGBA;

    unsigned int gl_id;
    glGenTextures(1, &gl_id);
    DEBUG_CODE(glCheckError();)
    glBindTexture(GL_TEXTURE_2D, gl_id);
    DEBUG_CODE(glCheckError();)
    int param = (textureFlags & 1)?GL_LINEAR: GL_NEAREST;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0,
                            GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    DEBUG_CODE(glCheckError();)

    if(textureFlags & 128){
        glGenerateMipmap(GL_TEXTURE_2D);
        DEBUG_CODE( glCheckError(); )
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    DEBUG_CODE(glCheckError();)

    HeroTexture* texture = (HeroTexture*)malloc(sizeof(HeroTexture));

    texture->glId = gl_id;
    texture->size = (HeroInt2){ surface->w, surface->h };
    texture->name = text;

    SDL_FreeSurface(surface);

    return texture;
}

HeroTexture* heroTextureConstruct(const char* name, HeroInt2 size, uint32_t glID)
{
    HeroTexture* texture = (HeroTexture*)malloc(sizeof(HeroTexture));
    texture->glId = glID;
    texture->size = size;
    texture->name = name;

    return texture;
}

uint32_t heroTextureGetGlID(const HeroTexture* texture)
{
    return texture->glId;
}

HeroInt2 heroTextureGetSize(const HeroTexture* texture)
{
    return texture->size;
}