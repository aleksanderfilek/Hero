#include"Hero/H_files.h"
#include<string.h>

#include"TinyFileDialogs/tinyfiledialogs.h"

char * heroFileDialogOpen(char const * aTitle, char const * aDefaultPathAndFile, int aNumOfFilterPatterns, 
	char const * const * aFilterPatterns, char const * aSingleFilterDescription, int aAllowMultipleSelects)
{
    char* path = tinyfd_openFileDialog(aTitle, aDefaultPathAndFile, aNumOfFilterPatterns, aFilterPatterns, aSingleFilterDescription, aAllowMultipleSelects);
    #ifdef _WIN32
    for(int i = 0; i < strlen( path ); i++)
    {
            if(path[i] == '\\')
            {
                    path[i] = '/';
            }
    }
    #endif
    return path;
}

char * heroFileSaveDialogOpen(char const * aTitle, char const * aDefaultPathAndFile, int aNumOfFilterPatterns,
	char const * const * aFilterPatterns, char const * aSingleFilterDescription)
{
    return tinyfd_saveFileDialog(aTitle, aDefaultPathAndFile, aNumOfFilterPatterns, aFilterPatterns, aSingleFilterDescription);
}