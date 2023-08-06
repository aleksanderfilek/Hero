#pragma once

#include "../Subsystem.h"
#include "../../Containers/Array.h"
#include "WindowObject.h"

class HERO_API WindowSubsystem : public Subsystem
{
private:
    static WindowSubsystem* instance;

    Array<WindowObject*> windowObjects;

public:
    static WindowSubsystem& Get() { return *instance; }

    WindowSubsystem();
    ~WindowSubsystem();

    void CreateWindow(const WindowConfiguration& WindowConfig);
    void CloseWindow(WindowObject* Window);
};