#pragma once

#include "../Definitions.h"

class HERO_API Platform
{
public:
    static const char* GetAbsoluteDirectory();
    static void SetAbsoluteDirectory(const char* Path);
};