#pragma once

#include "../Definitions.h"
#include "SubsystemManager.h"

class HERO_API Subsystem
{
friend class SubsystemManager;

private: 
    class SubsystemManager* subsystemManager = nullptr;

protected:
    bool updateEnabled = false;

public:
    virtual void Startup();
    virtual void Shutdown();
    virtual void Update();

    bool UpdateEnabled() const { return updateEnabled; }
    class SubsystemManager* GetSubsystemManager(){ return subsystemManager; }
};