#pragma once

#include"Texture.hpp"

namespace Hero
{

class RenderTarget : public Texture
{
private:
  uint32_t fbo;
  uint32_t rbo;

  ColorRGB clearColor = ColorRGB(255, 255, 255);
  uint32_t clearFlags;
  bool depthBuffer = false;
  bool stencilBuffer = false;
public:
  HERO RenderTarget(uint32_t Width, uint32_t Height, ColorChannel Channel, 
    bool DepthBuffer = false, bool StencilBuffer = false);
  HERO ~RenderTarget();

  HERO void Bind();
  HERO void Unbind();
  HERO void Clear();

  HERO void SetClearColor(ColorRGB ClearColor);

};

}