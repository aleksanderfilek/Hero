#pragma once

#include "../../../Definitions.h"
#include "../../../Resources/ResourceHandle.h"
#include "../../../GenericTypes/StringId.h"

class HERO_API IResourceLoader
{
public:
    virtual StringId GetName() = 0; 
    virtual ResourceHandle* Load(const uint8_t* Data, class ResourceSubsystem* Subsystem) = 0;
    virtual void Unload(ResourceHandle* Resource) = 0;
};