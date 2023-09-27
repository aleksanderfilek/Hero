#include "String.h"
#include <iostream>
String::String()
{

}

String::String(const String& Other)
{
    str = _strdup(Other.str);
    length = strlen(Other.str);
}

String::String(const char* Str)
{
    str = _strdup(Str);
    length = strlen(Str);
}

String::~String()
{
    if(str)
    {
        delete[] str;
        str = nullptr;
    }
}

String& String::operator +=(char Character)
{
    char* newStr = (char*)realloc(str, sizeof(char) * (length + 2));
    if (!newStr)
        return *this;

    str = newStr;
    str[length] = Character;
    str[length + 1] = '\0';
    length += 1;
    return *this;
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
    return str[Index];
}

void String::SetChar(int Position, char Character)
{
    str[Position] = Character;
}

void String::PopBack()
{
    SetChar(length - 1, '\0');
    length--;
}