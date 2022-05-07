#pragma once

namespace Hero
{
    HERO char* heroFileDialogOpen(char const * aTitle, char const * aDefaultPathAndFile, int aNumOfFilterPatterns, 
	    char const * const * aFilterPatterns, char const * aSingleFilterDescription, int aAllowMultipleSelects);

    HERO char* heroFileSaveDialogOpen(char const * aTitle, char const * aDefaultPathAndFile, int aNumOfFilterPatterns,
        char const * const * aFilterPatterns, char const * aSingleFilterDescription);
}