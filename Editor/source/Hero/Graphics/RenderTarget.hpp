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
  uint32_t RenderBufferId = 0;

  uint32_t Count = 0;
  uint32_t* BufferIds;

  uint32_t DepthBufferId = 0;

public:
  HERO RenderTarget(uint32_t Width, uint32_t Height, uint32_t Number = 1, RenderTargetConfig* Config = nullptr);
  HERO ~RenderTarget();

  HERO void BindBuffers();
  HERO void BindTexture();
  HERO void BlitToBuffer(uint32_t WriteBufferId, Int2 WrtiteBufferSize);

  inline uint32_t GetRenderBufferId(){ return RenderBufferId; }
  inline Int2 GetSize(){ return Size; }
};

}