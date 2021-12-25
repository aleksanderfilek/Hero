#pragma once

namespace Hero
{
    char * heroFileDialogOpen(char const * aTitle, char const * aDefaultPathAndFile, int aNumOfFilterPatterns, 
	    char const * const * aFilterPatterns, char const * aSingleFilterDescription, int aAllowMultipleSelects);

    char * heroFileSaveDialogOpen(char const * aTitle, char const * aDefaultPathAndFile, int aNumOfFilterPatterns,
        char const * const * aFilterPatterns, char const * aSingleFilterDescription);
}