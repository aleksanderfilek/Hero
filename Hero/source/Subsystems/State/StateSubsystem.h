#pragma once

#include "../Subsystem.h"

class HERO_API StateSubsystem : public Subsystem
{
private:
    static StateSubsystem* instance;

public:
    static StateSubsystem& Get() { return *instance; }

    StateSubsystem();

    virtual void Startup() override;
    virtual void Shutdown() override;
    virtual void Update() override;

private:
    class State* currentState = nullptr;
    class State* nextState = nullptr;

    void CheckState();

    class TimeSubsystem* timeSubsystem = nullptr;

public:
    void SetNextState(class State* NextState);
};