#pragma once

#include "IResourceConverter.h"

class HERO_API ShaderConverter : public IResourceConverter
{
public:
    virtual StringId GetName() override { return StringId("Shader"); }
    virtual void GetAcceptableExtensions(Array<String>& Extensions) override;
    virtual void Convert(const String& FilePath) override;
};