#pragma once

#include"../ThirdParty/SDL2/SDL.h"
#include<cstdint>

namespace Hero
{

enum class ColorSpace : uint8_t
{
    SRGB = 0,
    Linear = 1
};

enum class ColorChannel : uint8_t
{
    RED = 1,
    RGB = 3,
    RGBA = 4
};

HERO ColorChannel ConvertToColorChannel(uint8_t channel);
HERO int ConvertColorChannelToGl(ColorChannel channel);

typedef SDL_Color Color;

struct ColorHSV;

struct ColorRGB
{
    public:
        uint8_t r,g,b,a;
        constexpr ColorRGB(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 255)
            :r(_r), g(_g), b(_b), a(_a){}
        ColorRGB(const ColorRGB& obj)
            :r(obj.r), g(obj.g), b(obj.b), a(obj.a){}

        HERO ColorHSV convertToHSV() const;
        inline SDL_Color convertToSDLColor() const 
            { return (SDL_Color){.r = r, .g = g, .b = b, .a = a}; }

        constexpr static inline ColorRGB white(){
            return ColorRGB(255,255,255);
        }
};

struct ColorHSV
{
    public:
        float h,s,v;
        uint8_t a;

        HERO ColorHSV(float _h, float _s, float _v, uint8_t _a);
        HERO ColorHSV(const ColorHSV& obj);

        HERO ColorRGB convertToRGB() const;
};

}