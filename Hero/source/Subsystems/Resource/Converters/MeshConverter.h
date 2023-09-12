#pragma once

#include "IResourceConverter.h"

class HERO_API MeshConverter : public IResourceConverter
{
public:
    virtual StringId GetName() override { return StringId("Mesh"); }
    virtual void GetAcceptableExtensions(Array<String>& Extensions) override;
    virtual void Convert(const String& FilePath) override;

private:
    void ConvertObj(const String& FilePath);
};