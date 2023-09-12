#pragma once

#include "Definitions.h"
#include "GenericTypes/String.h"
#include "Subsystems/SubsystemManager.h"

enum class CoreState
{
    NotStarted = 0,
    Started,
    Stopped
};

class HERO_API Core
{
private:
    static Core* instance;
    
    String startupDirectory;

    CoreState state;

    SubsystemManager subsystemManager;
public:
    Core();
    ~Core();

    static Core& Get() { return *instance; }

    void Start();
    void Stop();
    void AddSubsystem(class Subsystem* Subsystem);

    const String& GetStartupDirectory() const { return startupDirectory; }
};