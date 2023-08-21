#pragma once

#include "../Definitions.h"
#include "../GenericTypes/String.h"

class HERO_API Platform
{
public:
    static String GetAbsoluteDirectory();
    static void SetAbsoluteDirectory(const String& Path);
};