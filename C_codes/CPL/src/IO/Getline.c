#include "Getline.h"
#include "CharInput.h"
#include <stdio.h>
#include "common.h"

BOOL didReachLimit(int numberOfRead, int limitationOfSpace)
{
    return numberOfRead >= limitationOfSpace - 1;
}

BOOL isReadable(int c)
{
    return c != EOF;
}

BOOL isEndOfLine(int c)
{
    return c == '\n';
}

int getLine(char *s, int limit)
{
    int c;
    int nRead = 0;

    while (isReadable(c = CharInput()))
    {
        *s++ = c;
        nRead++;
        if (isEndOfLine(c) || didReachLimit(nRead, limit))
            break;
    }

    *s = '\0';
    return nRead;
}
