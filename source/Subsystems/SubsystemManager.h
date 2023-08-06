#pragma once

#include "../Definitions.h"
#include "../Containers/Array.h"

class HERO_API SubsystemManager
{
private:
    Array<class Subsystem*> subsystems;
    Array<class Subsystem*> subsystemsToUpdate;

public:
    void AddSubsystem(class Subsystem* Subsystem, bool Startup);
    void Startup();
    void Shutdown();
    void Update();
};