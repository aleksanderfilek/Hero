#include "Path.h"

#include <cstring>
#include <cstdio>

const char* Path::Combine(const char* Path1, const char* Path2)
{
    char buffer[4096] = { '\0' };
    std::sprintf(buffer, "%s\\%s", Path1, Path2);
    char* str = _strdup(buffer);
    return str;
}