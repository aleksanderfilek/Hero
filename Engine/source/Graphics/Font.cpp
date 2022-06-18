#include"Font.hpp"
#include"../Utility/ByteOperations.hpp"

#include<iostream>

namespace Hero
{

HERO Font::Font()
{}

HERO Font::~Font()
{
    TTF_CloseFont(ttfFont);
}

HERO ResourceHandle* Font::Load(uint8_t* Data, Resources* system)
{
    int index = 0;
    uint32_t fontSize = ReadUint32(Data, &index);
    uint32_t pathSize = ReadUint32(Data, &index);
    char* path = new char[pathSize];
    ReadPtr(Data, &index, path, pathSize);

    Font* font = new Font();
    font->size = fontSize;
    font->ttfFont = TTF_OpenFont(path, fontSize);

    delete[] path;

    return font;
}

HERO void Font::Unload(ResourceHandle* resource)
{
    delete resource;
}

}