#include "SubsystemManager.h"
#include "Subsystem.h"
#include <iostream>

void SubsystemManager::AddSubsystem(Subsystem* Subsystem, bool Startup)
{
    Subsystem->subsystemManager = this;
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
    for(int i = subsystems.Length() - 1; i >= 0; i--)
    {
        subsystems[i]->Shutdown();
        delete subsystems[i];
    }
}

void SubsystemManager::Update()
{
    for(Subsystem* subsystem: subsystemsToUpdate)
    {
        subsystem->Update();
    }
}

SubsystemEvent& SubsystemManager::GetEvent(const StringId& Id)
{
    return subsystemEventsMap[Id];
}

void SubsystemManager::BroadcastEvent(const StringId& Id, void* Data)
{
    if(!subsystemEventsMap.Contains(Id))
    {
        return;
    }
    subsystemEventsMap[Id].Broadcast(Data);
}