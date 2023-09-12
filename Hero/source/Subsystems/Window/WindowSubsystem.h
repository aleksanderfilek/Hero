#pragma once

#include "../Subsystem.h"
#include "../../Containers/Array.h"
#include "../../GenericTypes/String.h"
#include "../../GenericTypes/StringId.h"
#include "../../Math/Int2.h"
#include "../../Graphics/Color.h"
#include <utility>

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

    StringId inputEventId = StringId("Input");
    void HandleEvent(void* Data);

public:
    static WindowSubsystem& Get() { return *instance; }

    WindowSubsystem(const StringId& Id, const WindowConfiguration& WindowConfig);

    virtual void Startup() override;
    virtual void Shutdown() override;
    virtual void Update() override;

private:
    Array<std::pair<StringId, WindowConfiguration>> windowsConfigurationsToCreate;
    Array<class WindowObject*> windowObjects;
    class WindowObject* currentWidnow = nullptr;

    void ReactToWindowFocusGained(class WindowObject* Window);
    void ReactToWindowFocusLost(class WindowObject* Window);

public:
    class WindowObject* CreateWindow(const StringId& Id, const WindowConfiguration& WindowConfig);
    void CloseWindow(class WindowObject* Window);

    class WindowObject* GetWindowById(const StringId& Id);
    class WindowObject* GetCurrentWindow() const;

private:
    class Mesh* screenMesh = nullptr;
    void CreateScreenMesh();
    class Shader* screenShader = nullptr;
    void CreateScreenShader();

public:
    class Mesh* GetScreenMesh();
    class Shader* GetScreenShader();
};