#pragma once

#include "../Definitions.h"
#include <cstdint>
#include <string>
#include "../Containers/Map.h"
#include <functional>

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

    static StringId None() { return StringId((uint32_t)0);}

    uint32_t operator *() const { return id; }
    //operator String();
    bool operator==(const StringId& Other) const;
    bool operator<(const StringId& Other) const;
};

namespace std
{
    template <>
    struct hash<StringId>
    {
        size_t operator()(const StringId& Key) const
        {
            return hash<uint32_t>()(*Key);
        }
    };
}