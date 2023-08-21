#pragma once

#include "IResourceConverter.h"

class HERO_API FontConverter : public IResourceConverter
{
public:
    virtual StringId GetName() override { return StringId("Font"); }
    virtual void GetAcceptableExtensions(Array<String>& Extensions) override;
    virtual void Convert(const String& FilePath) override;
};