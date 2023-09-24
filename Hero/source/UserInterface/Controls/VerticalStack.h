#pragma once

#include "Canvas.h"

class HERO_API VerticalStack : public Canvas
{
private:
	uint32_t spacing = 0;

public:

	virtual void Add(Control* Child) override;
	virtual void Remove(Control* Child) override;

	void SetSpacing(uint32_t Spacing);
	uint32_t GetSpacing() const { return spacing; }

	virtual void _InternalUpdateTransforms() override;
};