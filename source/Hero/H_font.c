#include<stdio.h>

#include"Hero/H_headers.h"

typedef TTF_Font HeroFont;

HeroFont* heroFontLoad(const char* path, int size)
{
    HeroFont* font = TTF_OpenFont(path, size);

    if(!font)
    {
            printf("Could not load font! SDL_ttf Error: %s\n", TTF_GetError());
            return NULL;
    }

    return font;
}

void heroFontUnload(void* font)
{
    TTF_CloseFont((HeroFont*)font);
}