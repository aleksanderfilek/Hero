#pragma once

#include "../Definitions.h"

class HERO_API Subsystem
{
private:
    bool updateEnabled = false;

public:
    virtual void Startup();
    virtual void Shutdown();
    virtual void Update();

    bool UpdateEnabled() const { return updateEnabled; }
};