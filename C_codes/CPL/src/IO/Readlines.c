#include "Readlines.h"
#include "charAlloc.h"
#include "Getline.h"
#include <string.h>

int readlines(char **linePointers, int limitNumberOfLines)
{
    char line[MAXLEN];
    char *currentAllocated;
    int lineLength;
    int numberOfLinesRead = 0;

    while ((lineLength = getLine(line, MAXLEN)))
    {
        if (numberOfLinesRead >= limitNumberOfLines ||
            !(currentAllocated = charAlloc(lineLength + 1))) /* NULL character */
            return ERR;

        strcpy(currentAllocated, line);
        linePointers[numberOfLinesRead++] = currentAllocated;
    }
    return numberOfLinesRead;
}
