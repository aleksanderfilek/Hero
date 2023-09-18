#pragma once

#include "../Definitions.h"
#include <cstring>
#include <cstdio>
#include <iostream>

#define STRING_MAX_LENGTH 2048

class HERO_API String
{
private:
    int length = 0;
    char* str = nullptr;

public:
    String();
    String(const String& Other);
    String(const char* Str);

    template<typename ... Args>
    String(const char* Format, Args... Arguments)
    {
        char buffer[STRING_MAX_LENGTH] = { '\0' };
        sprintf(buffer, Format, Arguments...);
        str = _strdup(buffer);
        length = strlen(str);
    }

    ~String();

    int Length() const { return length; }
    bool IsEmpty() const { return str == nullptr; }

    String& operator =(const String& Other);
    const char* operator *() const;
    bool operator==(const String& Rhs) const;
    char operator[](int Index) const;

    friend std::ostream& operator<<(std::ostream& stream, const String& rhs)
    {
        stream<<rhs.str;
        return stream;
    }
};