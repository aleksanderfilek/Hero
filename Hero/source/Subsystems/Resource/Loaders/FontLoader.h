#pragma once

#include "IResourceLoader.h"

class HERO_API FontLoader : public IResourceLoader
{
public:
    virtual StringId GetName() override { return StringId("Font"); } 
    virtual ResourceHandle* Load(const uint8_t* Data, class ResourceSubsystem* Subsystem) override;
    virtual void Unload(ResourceHandle* Resource) override;
};