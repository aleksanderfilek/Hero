#pragma once

#include "../Subsystem.h"
#include "InputKeys.h"
#include "../../Containers/Array.h"

class HERO_API InputSubsystem : public Subsystem
{
private:
    static InputSubsystem* instance;

    StringId inputEventId = StringId("Input");

    Array<class IInputDevice*> devices;

    class ControlMap* controlMap = nullptr;

    Array<class ControlScheme*> controlSchemes;

    bool showCursor = true;

public:
    static InputSubsystem& Get() { return *instance; }

    InputSubsystem();

    virtual void Startup() override;
    virtual void Shutdown() override;
    virtual void Update() override;

    class IInputDevice* GetDevice(StringId Id);

    void SetContolMap(class ControlMap* ControlMap);

    void PushContext(class ControlScheme* Scheme);
    class ControlScheme* PopContext();

    void ToggleCursor(bool Show);
    bool IsCursorVisible() const;
};