#ifndef D_SortLines_H
#define D_SortLines_H

/**********************************************************
 *
 * SortLines is responsible for ...
 *
 **********************************************************/

#include "common.h"
#define MAXLINES 100

int numcmp(char *, char*);
void SortLines_ParseCommandline(int argc, char *argv[]);
void SortLines_SetFieldOption(void);
void SortLines_NextFieldOption(void);
void SortLines_Destroy(void);
BOOL SortLines_IsNumeric(void);
BOOL SortLines_ShouldReverse(void);
BOOL SortLines_ShouldFold(void);
BOOL SortLines_IsDirectoryOrder(void);
unsigned int SortLines_StartField(void);
unsigned int SortLines_EndField(void);
int SortLines(void);

#endif  /* D_FakeSortLines_H */
