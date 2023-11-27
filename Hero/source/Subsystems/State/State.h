#pragma once

#include "../../Definitions.h"
#include "StateSubsystem.h"

class HERO_API State
{
private:
	StateSubsystem* stateSubsystem = nullptr;

	friend StateSubsystem;

public:
	StateSubsystem* GetStateSubsystem() const { return stateSubsystem; }

	virtual void Start(){}
	virtual void Update(float DeltaTime){}
	virtual void Close(){}
};