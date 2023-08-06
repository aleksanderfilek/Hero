#pragma once

#include "../Definitions.h"
#include <cstring>
#include <cstdio>
#include <iostream>

#define STRING_MAX_LENGTH 2048

class HERO_API String
{
private:
    char* str = nullptr;
    int length = 0;

public:
    String();
    String(const String& Other);
    String(const char* Str);

    template<typename ... Args>
    String(const char* Format, Args... Arguments)
    {
        char buffer[STRING_MAX_LENGTH] = { '\0' };
        sprintf(buffer, Format, Arguments...);
        str = strdup(buffer);
        length = strlen(str);
    }

    ~String();

    int Length() const { return length; }

    const char* operator *();
    bool operator==(const String& Rhs);

    friend std::ostream& operator<<(std::ostream& stream, const String& rhs)
    {
        stream<<rhs.str;
        return stream;
    }
};