#ifndef HERO_FILES_H_
#define HERO_FILES_H_

char * heroFileDialogOpen(char const * aTitle, char const * aDefaultPathAndFile, int aNumOfFilterPatterns, 
	char const * const * aFilterPatterns, char const * aSingleFilterDescription, int aAllowMultipleSelects);

char * heroFileSaveDialogOpen(char const * aTitle, char const * aDefaultPathAndFile, int aNumOfFilterPatterns,
	char const * const * aFilterPatterns, char const * aSingleFilterDescription);

char * heroFileInputBox(char const* aTitle, char const* aMessage, char const* aDefaultInput);

#endif