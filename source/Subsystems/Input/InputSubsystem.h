#pragma once

#include "../Subsystem.h"

class HERO_API InputSubsystem : public Subsystem
{
private:
    static InputSubsystem* instance;

    StringId inputEventId = StringId("Input");

public:
    static InputSubsystem& Get() { return *instance; }

    InputSubsystem();

    virtual void Startup() override;
    virtual void Shutdown() override;
    virtual void Update() override;
};