#include "Core.h"
#include "Utility/Platform.h"
#include <iostream>

Core* Core::instance = nullptr;

Core::Core()
{
    instance = this;
    startupDirectory = Platform::GetAbsoluteDirectory();

    state = CoreState::NotStarted;
}

Core::~Core()
{
    delete[] startupDirectory;
}

void Core::Start()
{
    subsystemManager.Startup();

    state = CoreState::Started;
    while(state == CoreState::Started)
    {
        subsystemManager.Update();
    }

    subsystemManager.Shutdown();
}

void Core::Stop()
{
    state = CoreState::Stopped;
}

void Core::AddSubsystem(class Subsystem* Subsystem)
{
  subsystemManager.AddSubsystem(Subsystem, state == CoreState::Started);
}

