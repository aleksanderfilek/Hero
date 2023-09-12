#pragma once

#include "IResourceLoader.h"

class HERO_API MaterialLoader : public IResourceLoader
{
public:
    virtual StringId GetName() override { return StringId("Material"); } 
    virtual ResourceHandle* Load(const uint8_t* Data, class ResourceSubsystem* Subsystem) override;
    virtual void Unload(ResourceHandle* Resource) override;
};