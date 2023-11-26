#pragma once

#include "IResourceConverter.h"

class HERO_API MeshConverter : public IResourceConverter
{
public:
    virtual StringId GetName() override { return StringId("Mesh"); }
    virtual void GetAcceptableExtensions(Array<const char*>& Extensions) override;
    virtual void Convert(const char* FilePath) override;

private:
    void ConvertObj(const char* FilePath);
};