#pragma once

#include "../../../Definitions.h"
#include "../../../GenericTypes/StringId.h"
#include "../../../Containers/Array.h"

class HERO_API IResourceConverter
{
public:
    virtual StringId GetName() = 0; 
    virtual void GetAcceptableExtensions(Array<const char*>& Extensions) = 0;
    virtual void Convert(const char* FilePath) = 0;
};