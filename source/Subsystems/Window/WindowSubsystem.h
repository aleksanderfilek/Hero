#pragma once

#include "../Subsystem.h"
#include "../../Containers/Array.h"
#include "../../GenericTypes/String.h"
#include "../../Math/Int2.h"
#include "../../Graphics/Color.h"

struct WindowConfiguration
{
    String Title;
    Int2 Size;
    Color BackgroundColor;
};

class HERO_API WindowSubsystem : public Subsystem
{
private:
    static WindowSubsystem* instance;

    Array<class WindowObject*> windowObjects;

public:
    static WindowSubsystem& Get() { return *instance; }

    WindowSubsystem();
    ~WindowSubsystem();

    class WindowObject* CreateWindow(const WindowConfiguration& WindowConfig);
    void CloseWindow(class WindowObject* Window);
};