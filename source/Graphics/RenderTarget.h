#pragma once

#include "../Definitions.h"
#include"../Math/Int2.h"
#include <cstdint>

class HERO_API RenderTarget
{
private:
	Int2 size;
	uint32_t renderBufferId = 0;
	uint32_t bufferId = 0;

    bool depthBufferEnabled = false;
	uint32_t depthBufferId = 0;

public:
	RenderTarget(Int2 Size, bool EnableDepthBuffer = false);
	~RenderTarget();

	void BindBuffers();
	void UnbindBuffers();
	void BindTexture();
	void BlitToBuffer(uint32_t WriteBufferId, Int2 WrtiteBufferSize);

	uint32_t GetRenderBufferId() const { return renderBufferId; }
	Int2 GetSize() const { return size; }
};