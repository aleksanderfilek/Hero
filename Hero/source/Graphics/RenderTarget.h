#pragma once

#include "../Definitions.h"
#include"../Math/Int2.h"
#include <cstdint>

class HERO_API RenderTarget
{
private:
	Int2 size;
	uint32_t renderBufferId;
	uint32_t bufferId;

    bool depthBufferEnabled = false;
	uint32_t depthBufferId = 0;

public:
	RenderTarget(Int2 Size, bool EnableDepthBuffer = false);
	~RenderTarget();

	void BindBuffers();
	void UnbindBuffers();
	void BindTexture(int Slot = 0);
	void BlitToBuffer(uint32_t WriteBufferId, Int2 WrtiteBufferSize);

	uint32_t GetRenderBufferId() const { return renderBufferId; }
	Int2 GetSize() const { return size; }

	void Clear();
};