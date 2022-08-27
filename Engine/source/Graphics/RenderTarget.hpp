#pragma once

#include"../Core/Math.hpp"
#include<vector>

namespace Hero
{

struct RenderTargetConfig
{
  std::vector<int> Format;
  bool DepthBuffer = false;
};

class RenderTarget
{
private:
  Int2 Size;
  uint32_t RenderBufferId;

  uint32_t Count;
  uint32_t* BufferIds;

  uint32_t DepthBufferId;

public:
  HERO RenderTarget(uint32_t Width, uint32_t Height, uint32_t Number = 1, RenderTargetConfig* Config = nullptr);
  HERO ~RenderTarget();

  HERO void BindBuffers();
  HERO void BindTexture();
};

}