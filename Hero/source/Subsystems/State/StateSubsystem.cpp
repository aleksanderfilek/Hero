#include "StateSubsystem.h"
#include "State.h"
#include "../Time/TimeSubsystem.h"

StateSubsystem* StateSubsystem::instance = nullptr;

StateSubsystem::StateSubsystem()
{
	instance = this;
}

void StateSubsystem::Startup()
{
	Subsystem::Startup();

	timeSubsystem = &TimeSubsystem::Get();
}

void StateSubsystem::Shutdown()
{
	Subsystem::Shutdown();

	if (nextState)
	{
		delete nextState;
	}

	if (currentState)
	{
		currentState->Close();
		delete currentState;
	}
}

void StateSubsystem::Update()
{
	Subsystem::Update();

	CheckState();

	if (currentState)
	{
		currentState->Update(timeSubsystem->GetDeltaTime());
	}
}

void StateSubsystem::CheckState()
{
	if (nextState)
	{
		if (currentState)
		{
			currentState->Close();
			delete currentState;
		}

		currentState = nextState;
		nextState = nullptr;
		currentState->Start();
	}
}

void StateSubsystem::SetNextState(class State* NextState)
{
	if (nextState)
	{
		delete nextState;
	}

	nextState = NextState;
}