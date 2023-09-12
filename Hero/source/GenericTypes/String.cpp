#include "String.h"
#include <iostream>
String::String()
{

}

String::String(const String& Other)
{
    str = _strdup(Other.str);
    length = strlen(Other.str);
    // str = new char[length + 1]{0};
    // strncpy(str, Other.str, length);
}

String::String(const char* Str)
{
    str = _strdup(Str);
    length = strlen(Str);
    // str = new char[length + 1]{0};    
    // strncpy(str, Str, length);
}

String::~String()
{
    if(str)
    {
        delete[] str;
        str = nullptr;
    }
}

String& String::operator =(const String& Other)
{
    str = _strdup(Other.str);
    length = strlen(str);
    return *this;
}

const char* String::operator *() const
{
    return str;
}

bool String::operator==(const String& Rhs) const
{
    if(length != Rhs.length)
    {
        return false;
    }

    for(int i = 0; i < length; i++)
    {
        if(str[i] != Rhs.str[i])
        {
            return false;
        }
    }

    return true;
}

char String::operator[](int Index) const
{
    if(Index >= Length())
    {
        return 0;
    }

    return str[Index];
}