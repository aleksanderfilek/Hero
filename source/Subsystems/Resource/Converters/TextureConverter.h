#pragma once

#include "IResourceConverter.h"

class HERO_API TextureConverter : public IResourceConverter
{
public:
    virtual StringId GetName() override { return StringId("Texture"); }
    virtual void GetAcceptableExtensions(Array<String>& Extensions) override;
    virtual void Convert(const String& FilePath) override;
};