#pragma once

#include "../Definitions.h"
#include <cstdint>
#include "String.h"
#include "../Containers/Map.h"

uint32_t HashCrc32(const char* str);

class HERO_API StringId
{
private:
    uint32_t id = 0;

    void Insert(const char* Str);

    static Map<uint32_t, const char*> data;

public:
    StringId();
    StringId(uint32_t Id);
    StringId(const StringId& Other);
    StringId(const char* Str);
    StringId(const String& Str);

    static StringId None() { return StringId((uint32_t)0);}

    uint32_t operator *(){ return id; }
    operator String();
    bool operator==(const StringId& Other);
};