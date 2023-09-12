#pragma once

#include "../Definitions.h"
#include "../GenericTypes/StringId.h"
#include "../Containers/Map.h"

class HERO_API UniformBlock
{
private:
    uint32_t id;
    uint32_t ubo;

    uint32_t size = 0;
    Map<StringId, uint32_t> offsetMap;

    void BindValue(uint32_t Offset, uint32_t Size, void* ValuePtr);

public:

    template<typename T>
    void Register(StringId Id)
    {
        offsetMap.Add( Id, size );
        int byteSize = sizeof(T);
        int bytes = (byteSize / 16) * 16;
        bytes += (byteSize % 16 > 0) ? 16 : 0;
        size += bytes;
    }

    void Apply(uint32_t Id);

    template<typename T>
    void Set(StringId Id, T Value)
    {
        if (!offsetMap.Contains(Id))
        {
            return;
        }

        uint32_t offset = offsetMap[Id];
        BindValue(offset, sizeof(T), &Value);
    }
};
