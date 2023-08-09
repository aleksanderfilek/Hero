#pragma once

#include "../Subsystem.h"
#include "../../Containers/Array.h"
#include "../../GenericTypes/String.h"
#include "../../GenericTypes/StringId.h"
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

    StringId inputEventId = StringId("Input");
    void HandleEvent(void* Data);

public:
    static WindowSubsystem& Get() { return *instance; }

    WindowSubsystem();

    virtual void Startup() override;
    virtual void Shutdown() override;

    class WindowObject* CreateWindow(const WindowConfiguration& WindowConfig);
    void CloseWindow(class WindowObject* Window);
};