#include "Switcher.h"
#include "../../Math/Math.h"

void Switcher::SetActiveControlIndex(int Index)
{
	activeControlIndex = Clamp(Index, 0, GetChildrenCount() - 1);
}

int Switcher::GetActiveControlIndex() const
{
	return activeControlIndex;
}

void Switcher::_InternalUpdateHoverState(const Int2& MousePosition)
{
    Control::_InternalUpdateHoverState(MousePosition);
    if (!IsHovered())
        return;

    if (activeControlIndex >= GetChildrenCount())
    {
        return;
    }

    children[activeControlIndex]->_InternalUpdateHoverState(MousePosition);
}

void Switcher::SetHover(bool Hovered)
{
    Control::SetHover(Hovered);

    if (activeControlIndex >= GetChildrenCount())
    {
        return;
    }

    children[activeControlIndex]->SetHover(Hovered);
}

bool Switcher::_InternalUpdateButtonClicks(MouseCode Code)
{
    if (!IsHovered())
        return false;

    if (activeControlIndex < GetChildrenCount())
    {
        bool result = children[activeControlIndex]->_InternalUpdateButtonClicks(Code);
        if (result)
            return true;
    }

    return Control::_InternalUpdateButtonClicks(Code);
}

void Switcher::Draw(class ISpriteRenderer* SpriteRenderer)
{
    if (activeControlIndex >= GetChildrenCount())
    {
        return;
    }

    children[activeControlIndex]->Draw(SpriteRenderer);
}