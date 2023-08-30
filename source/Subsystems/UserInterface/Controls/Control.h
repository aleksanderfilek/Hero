#pragma once

#include "../../../Definitions.h"
#include "../../../Math/Int2.h"
#include "../../../GenericTypes/Event.h"
#include "../../../Math/Float2.h"
#include "../../Input/InputKeys.h"

EVENT_DISPATCHER(ControlEvent);

enum class HorizontalAlligment
{
    LEFT = 0,
    CENTER,
    RIGHT,
    STRETCH
};

enum class VerticalAlligment
{
    TOP = 0,
    CENTER,
    BOTTOM,
    STRETCH
};

enum class VisibilityState
{
    HIDDEN = 0,
    VISIBLE
};

class HERO_API Control
{
private:
    class Widget* widget = nullptr;
    Control* parent = nullptr;

    Int2 position;
    Int2 size;
    HorizontalAlligment horizontalAlligment = HorizontalAlligment::LEFT;
    VerticalAlligment verticalAlligment = VerticalAlligment::TOP;
    Float2 pivot;

    Int2 absolutePosition;
    Int2 absoluteSize;    

public:
    virtual void _InternalSetWidget(class Widget* Widget);
    class Widget* GetWidget() const;

    void AttachToControl(Control* ControlToAttachTo);
    Control* GetParent() const;

    void SetPosition(const Int2& Position);
    Int2 GetPosition() const;
    void SetSize(const Int2& Size);
    Int2 GetSize() const;
    void SetHorizontalAlligment(HorizontalAlligment Alligment);
    HorizontalAlligment GetHorizontalAlligment() const;
    void SetVerticalAlligment(VerticalAlligment Alligment);
    VerticalAlligment GetVerticalAlligment() const;
    void SetPivot(const Float2& Pivot);

    Int2 GetAbsolutePosition() const;
    Int2 GetAbsoluteSize() const;

    void _InternalUpdateTransforms();

private:
    VisibilityState visibilityState = VisibilityState::VISIBLE;

public:
    void SetVisibility(VisibilityState Visibility);

private:
    bool hovered = false;

public:
    ControlEvent OnLeftClick;
    ControlEvent OnRightClick;
    ControlEvent OnHoverEnter;
    ControlEvent OnHoverExit;

    virtual void _InternalUpdateHoverState(const Int2& MousePosition);
    bool IsHovered() const;
    virtual void SetHover(bool Hovered);

    virtual bool _InternalUpdateButtonClicks(MouseCode Code);

private:
    bool updateEnabled = false;

public:
    void SetUpdateEnabled(bool Enable);
    virtual void Update(float DeltaTime){}
};