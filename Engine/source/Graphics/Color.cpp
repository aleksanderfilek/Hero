#include"Color.hpp"
#include"../Core/Math.hpp"
#include"../ThirdParty/GL/Gl.hpp"

#include<cmath>

namespace Hero
{

HERO ColorChannel ConvertToColorChannel(uint8_t channel)
{
    return static_cast<ColorChannel>(channel);
}

HERO int ConvertColorChannelToGl(ColorChannel channel)
{
    int gl = 0;

    switch(channel)
    {
        case ColorChannel::RED:
            gl = GL_RED;
            break;
        case ColorChannel::RGB:
            gl = GL_RGB;
            break;
        case ColorChannel::RGBA:
            gl = GL_RGBA;
            break;
    }

    return gl;
}

HERO ColorHSV ColorRGB::convertToHSV() const
{
    float tr = (float)r/255.0f;
    float tg = (float)g/255.0f;
    float tb = (float)b/255.0f;

    float cmax = 0.0f, cmin = 0.0f;
    cmax = max(tr, max(tg, tb));
    cmin = min(tr, min(tg, tb));

    float delta = cmax - cmin;
    float h;
    if(delta == 0.0f)
    {
        h = 0.0f;
    }
    else if(cmax == tr)
    {
        h = (tg - tb);
        h /= delta;
        h = fmod(h, 6);
        h *= 60.0f;
    }
    else if(cmax == tg)
    {
        h = (tb - tr);
        h /= delta;
        h = fmod(h, 2);
        h *= 60.0f;
    }
    else if(cmax == tb)
    {
        h = (tr - tg);
        h /= delta;
        h = fmod(h, 4);
        h *= 60.0f;
    }

    float s = (cmax == 0.0f)? 0: delta/cmax;

    float v = cmax;

    return ColorHSV(h, s, v, a);
}

HERO ColorHSV::ColorHSV(float _h, float _s, float _v, uint8_t _a)
    :h(_h), s(_s), v(_v), a(_a)
{}

HERO ColorHSV::ColorHSV(const ColorHSV& obj)
    :h(obj.h), s(obj.s), v(obj.v), a(obj.a)
{}


HERO ColorRGB ColorHSV::convertToRGB() const
{
    float c = v*s;
    float x = c * (1 - fabs( fmod(h/60.0f,2.0f) - 1));
    uint8_t m = v - c;

    int region = (int)(h / 60.0f);
    float tr, tg, tb;
    switch(region)
    {
        case 0:
            tr = c;
            tg = x;
            tb = 0.0f;
            break;
        case 1:
            tr = x;
            tg = c;
            tb = 0.0f;
            break;
        case 2:
            tr = 0.0f;
            tg = c;
            tb = x;
            break;
        case 3:
            tr = 0.0f;
            tg = x;
            tb = c;
            break;
        case 4:
            tr = x;
            tg = 0.0f;
            tb = c;
            break;
        case 5:
            tr = c;
            tg = 0.0f;
            tb = x;
            break;
    }

    uint8_t r = (uint8_t)((tr+m)*255.0f);
    uint8_t g = (uint8_t)((tg+m)*255.0f);
    uint8_t b = (uint8_t)((tb+m)*255.0f);

    return ColorRGB(r,g,b,a);
}

}