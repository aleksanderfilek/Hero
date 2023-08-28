#pragma once

#include "Control.h"

#include "../../../Containers/Array.h"

class HERO_API Canvas : public Control
{
protected:
    Array<Control*> children;

public:
    virtual void Add(Control* Child);
    virtual void Remove(Control* Child);
    virtual void ClearChildren();
    virtual int GetChildrenCount();
    virtual void GetChildren(Array<Control*>& Children);

    virtual void SetHover(bool Hovered) override;
};