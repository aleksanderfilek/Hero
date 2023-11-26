#pragma once

#include "Definitions.h"
#include "Subsystems/SubsystemManager.h"
#include <string>

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
    
    const char* startupDirectory;

    CoreState state;

    SubsystemManager subsystemManager;
public:
    Core();
    ~Core();

    static Core& Get() { return *instance; }

    void Start();
    void Stop();
    void AddSubsystem(class Subsystem* Subsystem);

    const char* GetStartupDirectory() const { return startupDirectory; }
};