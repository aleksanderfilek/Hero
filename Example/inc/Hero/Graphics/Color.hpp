#pragma once

#include"ThirdParty.hpp"
#include<cstdint>

namespace Hero
{

typedef SDL_Color Color;

class ColorHSV;

class ColorRGB
{
    public:
        uint8_t r,g,b,a;

        HERO ColorRGB(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 255);
        HERO ColorRGB(float _r, float _g, float _b, float _a = 1.0f);
        HERO ColorRGB(const ColorRGB& obj);

        HERO ColorHSV convertToHSV() const;
        inline SDL_Color convertToSDLColor() const 
            { return (SDL_Color){.r = r, .g = g, .b = b, .a = a}; }
};

class ColorHSV
{
    public:
        float h,s,v;
        uint8_t a;

        HERO ColorHSV(float _h, float _s, float _v, uint8_t _a);
        HERO ColorHSV(const ColorHSV& obj);

        HERO ColorRGB convertToRGB() const;
};

}