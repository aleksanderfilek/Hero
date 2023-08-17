#pragma once

#include "IResourceLoader.h"

class TextureLoader : public IResourceLoader
{
public:
    virtual StringId GetName() override { return StringId("Texture"); } 
    virtual ResourceHandle* Load(const uint8_t* Data, class ResourceSubsystem* Subsystem) override;
    virtual void Unload(ResourceHandle* Resource) override;
};