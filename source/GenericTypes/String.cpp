#include "String.h"

String::String()
{

}

String::String(const String& Other)
{
    str = strdup(Other.str);
    length = strlen(str);
}

String::String(const char* Str)
{
    str = strdup(Str);
    length = strlen(str);
}

String::~String()
{
    if(str)
    {
        delete[] str;
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
