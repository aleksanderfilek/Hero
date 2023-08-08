#include "String.h"
#include <iostream>
String::String()
{

}

String::String(const String& Other)
{
    str = strdup(Other.str);
    length = strlen(Other.str);
    // str = new char[length + 1]{0};
    // strncpy(str, Other.str, length);
}

String::String(const char* Str)
{
    str = strdup(Str);
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

const char* String::operator *()
{
    return str;
}

bool String::operator==(const String& Rhs)
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
