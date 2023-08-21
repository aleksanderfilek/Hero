#pragma once

#include "../Definitions.h"
#include "../GenericTypes/StringId.h"

class HERO_API ResourceHandle
{
friend class ResourceSubsystem;

private:
    class ResourceSubsystem* resourceSubsystem = nullptr;
    StringId id;

public:
    class ResourceSubsystem* GetResourceSubsystem() const { return resourceSubsystem; }
};
