#include<SDL2/SDL_ttf.h>

typedef TTF_Font H_Font;

H_Font* H_Font_Load(const char* path, int size)
{
    H_Font* font = TTF_OpenFont(path, size);

    if(!font)
    {
            printf("Could not load font! SDL_ttf Error: %s\n", TTF_GetError());
            return NULL;
    }

    return font;
}

void H_Font_Unload(H_Font* font)
{
    TTF_CloseFont(font);
}