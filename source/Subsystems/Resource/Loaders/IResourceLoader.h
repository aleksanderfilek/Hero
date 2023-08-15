#pragma once

#include "../../../Resources/ResourceHandle.h"
#include "../../../GenericTypes/StringId.h"

class IResourceLoader
{
public:
    virtual StringId GetName(){}; 
    virtual ResourceHandle* Load(const uint8_t* Data){};
    virtual void Unload(ResourceHandle* Resource){};
};