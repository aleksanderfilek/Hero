#pragma once

namespace Hero
{
    HERO char* FileDialogOpen(char const * aTitle, char const * aDefaultPathAndFile, int aNumOfFilterPatterns, 
	    char const * const * aFilterPatterns, char const * aSingleFilterDescription, int aAllowMultipleSelects);

    HERO char* FileSaveDialogOpen(char const * aTitle, char const * aDefaultPathAndFile, int aNumOfFilterPatterns,
        char const * const * aFilterPatterns, char const * aSingleFilterDescription);
}