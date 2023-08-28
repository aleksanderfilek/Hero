#pragma once

#include "../Subsystem.h"
#include "../../Containers/Array.h"

class HERO_API UserInterfaceSubsystem : public Subsystem
{
private:
    static UserInterfaceSubsystem* instance;

public:
    static UserInterfaceSubsystem& Get() { return *instance; }

    UserInterfaceSubsystem();

    virtual void Startup() override;
    virtual void Shutdown() override;
    virtual void Update() override;

private:
    Array<class Widget*> widgets;

    void ReactToMouseMotion(const Int2& Position, const Int2& MotionVector);

public:
    void AddWidget(class Widget* Widget);
    void RemoveWidget(class Widget* Widget);
};