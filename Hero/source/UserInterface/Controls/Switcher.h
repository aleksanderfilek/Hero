#pragma once

#include "Canvas.h"

class HERO_API Switcher : public Canvas
{
private:
	int activeControlIndex = 0;

public:
	void SetActiveControlIndex(int Index);
	int GetActiveControlIndex() const;

	virtual void _InternalUpdateHoverState(const Int2& MousePosition) override;
	virtual void SetHover(bool Hovered) override;
	virtual bool _InternalUpdateButtonClicks(MouseCode Code) override;

	virtual void Draw(class ISpriteRenderer* SpriteRenderer) override;
};