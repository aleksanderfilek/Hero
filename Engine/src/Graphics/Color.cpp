#include"Color.hpp"
#include"Math.hpp"

#include<cmath>

namespace Hero
{

ColorRGB::ColorRGB(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 255)
    :r(_r), g(_g), b(_b), a(_a)
{}

ColorRGB::ColorRGB(float _r, float _g, float _b, float _a = 1.0f)
{
    r = (float)_r/255.0f;
    g = (float)_g/255.0f;
    b = (float)_b/255.0f;
    a = (float)_a/255.0f;
}

ColorRGB::ColroRGB(const ColorRGB& obj)
    :r(obj.r), g(obj.g), b(obj.b), a(obj.a)
{}

ColorRGB::ColorHSV convertToHSV()
{
    float tr = (float)_r/255.0f;
    float tg = (float)_g/255.0f;
    float tb = (float)_b/255.0f;

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
        h %= 6;
        h *= 60.0f;
    }
    else if(cmax == tg)
    {
        h = (tb - tr);
        h /= delta;
        h %= 2;
        h *= 60.0f;
    }
    else if(cmax == tb)
    {
        h = (tr - tg);
        h /= delta;
        h %= 4;
        h *= 60.0f;
    }

    float s = (cmax == 0.0f)? 0: delta/cmax;

    float v = cmax;

    return ColorHSV(h, s, v, a);
}

ColorHSV::ColorHSV(float _h, float _s, float _v, float _a)
    :h(_h), s(_s), v(_v), a(_a)
{}

ColorHSV::ColorHSV(const ColorHSV& obj)
    :h(obj.h), s(obj.s), v(obj.v), a(obj.a)
{}


ColorRGB ColorHSV::convertToRGB() const
{
    float c = v*s;
    float x = c * (1 - fabs( ((h/60.0f)%2) - 1);
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

    uint8_t r = (uint8_t((tr+m)*255.0f);
    uint8_t g = (uint8_t((tg+m)*255.0f);
    uint8_t b = (uint8_t((tb+m)*255.0f);

    return ColorRGB(r,g,b,a);
}

}