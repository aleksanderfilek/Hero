#include"Font.hpp"

#include<iostream>
#include<cstdlib>
            
namespace Hero
{

Font::Font(const char* _path, uint32_t _size)
{
    font = TTF_OpenFont(_path, _size);

    if(!font)
    {
        std::cout<<"Could not load font! SDL_ttf Error: "<< TTF_GetError()<<std::endl;
        exit(-1);
    }
}

Font::~Font()
{
    TTF_CloseFont(font);
}

}