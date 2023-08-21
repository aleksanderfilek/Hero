#pragma once

#include "../../../Definitions.h"
#include "../../../GenericTypes/StringId.h"
#include "../../../Containers/Array.h"

class HERO_API IResourceConverter
{
public:
    virtual StringId GetName() = 0; 
    virtual void GetAcceptableExtensions(Array<String>& Extensions) = 0;
    virtual void Convert(const String& FilePath) = 0;
};