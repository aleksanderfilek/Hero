#include"Hero/H_files.h"

#include"TinyFileDialogs/tinyfiledialogs.h"

char * heroFileDialogOpen(char const * aTitle, char const * aDefaultPathAndFile, int aNumOfFilterPatterns, 
	char const * const * aFilterPatterns, char const * aSingleFilterDescription, int aAllowMultipleSelects)
{
    return tinyfd_openFileDialog(aTitle, aDefaultPathAndFile, aNumOfFilterPatterns, aFilterPatterns, aSingleFilterDescription, aAllowMultipleSelects);
}

char * heroFileSaveDialogOpen(char const * aTitle, char const * aDefaultPathAndFile, int aNumOfFilterPatterns,
	char const * const * aFilterPatterns, char const * aSingleFilterDescription)
{
    return tinyfd_saveFileDialog(aTitle, aDefaultPathAndFile, aNumOfFilterPatterns, aFilterPatterns, aSingleFilterDescription);
}