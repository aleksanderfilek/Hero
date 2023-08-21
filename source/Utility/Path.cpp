#include "Path.h"

String Path::Combine(const String& Path1, const String& Path2)
{
    return String("%s\\%s", *Path1, *Path2);
}