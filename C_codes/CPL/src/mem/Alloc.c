#include "Alloc.h"
#include "common.h"
#include <stdio.h>

static char allocBuffer[ALLOCSIZE];
static char *allocp = allocBuffer;

static BOOL IsOutOfBounds(char * testPointer)
{
    return testPointer < allocBuffer ||
        testPointer >= allocBuffer + ALLOCSIZE;
}

char *alloc(int size)
{
    if (IsOutOfBounds(allocp + size - 1))
        return NULL;

    allocp += size;
    return allocp - size;
}

void afree(char *allocated)
{
    if (IsOutOfBounds(allocated))
        return;
    allocp = allocated;
}

void areset(void)
{
    allocp = allocBuffer;
}
