#include "StringId.h"

Map<uint32_t, const char*> StringId::data;

uint32_t HashCrc32(const char* str)
{
	uint32_t crc = 0xFFFFFFFF;
	uint32_t n = strlen(str);

	for (uint32_t i = 0; i < n; i++) {
		char ch = str[i];
		for (size_t j = 0; j < 8; j++) {
			uint32_t b = (ch ^ crc) & 1;
			crc >>= 1;
			if (b) crc = crc ^ 0xEDB88320;
			ch >>= 1;
		}
	}

	return ~crc;
}

StringId::StringId()
{
    if(data.Size() == 0)
    {
        data.Add(0, {"None"});
    }
}

StringId::StringId(uint32_t Id) : StringId()
{
    id = Id;
}

StringId::StringId(const StringId& Other) : StringId()
{
    id = Other.id;
}

StringId::StringId(const char* Str) : StringId()
{
    Insert(Str);
}

StringId::StringId(const String& Str) : StringId()
{
    Insert(*const_cast<String&>(Str));
}

void StringId::Insert(const char* Str)
{
    id = HashCrc32(Str);
    data.Add(id, strdup(Str));
}

StringId::operator String()
{
    if(data.Contains(id))
    {
        return data[id];
    }

    return StringId::None();
}

bool StringId::operator==(const StringId& Other)
{
    return id == Other.id;
}