#include "StringId.h"

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
	id = 0;
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

void StringId::Insert(const char* Str)
{
    id = HashCrc32(Str);
}

//StringId::operator String()
//{
//    if(data.Contains(id))
//    {
//        return data[id];
//    }
//
//    return StringId::None();
//}

bool StringId::operator==(const StringId& Other) const
{
    return id == Other.id;
}

bool StringId::operator<(const StringId& Other) const
{
    return id < Other.id;
}