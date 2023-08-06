#include "SubsystemManager.h"
#include "Subsystem.h"

void SubsystemManager::AddSubsystem(Subsystem* Subsystem, bool Startup)
{
    subsystems.Add(Subsystem);

    if(Subsystem->UpdateEnabled())
    {
        subsystemsToUpdate.Add(Subsystem);
    }

    if(Startup)
    {
        Subsystem->Startup();
    }
}

void SubsystemManager::Startup()
{
    for(Subsystem* subsystem: subsystems)
    {
        subsystem->Startup();
    }
}

void SubsystemManager::Shutdown()
{
    for(Subsystem* subsystem: subsystems)
    {
        subsystem->Shutdown();
    }
}

void SubsystemManager::Update()
{
    for(Subsystem* subsystem: subsystemsToUpdate)
    {
        subsystem->Update();
    }
}