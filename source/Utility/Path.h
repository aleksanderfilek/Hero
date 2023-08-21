#pragma once

#include "../Definitions.h"
#include "../GenericTypes/String.h"

class HERO_API Path
{
public:
    static String Combine(const String& Path1, const String& Path2);
};