#include "Core.h"

Core* Core::instance = nullptr;

Core::Core()
{
    instance = this;

    state = CoreState::NotStarted;
}

Core::~Core()
{

}

void Core::Start()
{
    subsystemManager.Startup();

    state = CoreState::Started;
    while(state == CoreState::Started)
    {

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