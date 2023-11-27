#pragma once

#include "../Definitions.h"
#include "../Containers/Array.h"
#include "../Containers/Map.h"
#include "../GenericTypes/StringId.h"
#include "../GenericTypes/Event.h"

EVENT_DISPATCHER(SubsystemEvent, void*)

class HERO_API SubsystemArray : public Array<class Subsystem*>{};
class HERO_API SubsystemEventsMap : public Map<StringId, SubsystemEvent>{};

class HERO_API SubsystemManager
{
private:
    SubsystemArray subsystems;
    SubsystemArray subsystemsToUpdate;

    SubsystemEventsMap subsystemEventsMap;

public:
    void AddSubsystem(class Subsystem* Subsystem, bool Startup);
    void Startup();
    void Shutdown();
    void Update();

    SubsystemEvent& GetEvent(const StringId& Id);
    void BroadcastEvent(const StringId& Id, void* Data);
};