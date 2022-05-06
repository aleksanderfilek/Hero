#include"Platform.hpp"

#include <stdio.h>

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

namespace Hero
{

std::string GetCurrentDirectory()
{
  char path[FILENAME_MAX];
  GetCurrentDir(path, FILENAME_MAX);
  path[FILENAME_MAX - 1] = '\0';
  return std::string(path);
}

}