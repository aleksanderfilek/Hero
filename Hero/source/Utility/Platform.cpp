#include "Platform.h"

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <windows.h>
#include <cstring>

#define FILEPATH_MAX 4098

String Platform::GetAbsoluteDirectory()
{
    char buffer[FILEPATH_MAX] = {};
	GetCurrentDir(buffer, FILEPATH_MAX);

    int length = strlen(buffer) + 1;
    char* pathStr = new char[length];
    memcpy(pathStr, buffer, length * sizeof(char));
	String path(pathStr);
    delete[] pathStr;

    return path;
}

void Platform::SetAbsoluteDirectory(const String& Path)
{
	SetCurrentDirectoryA(*Path);
}