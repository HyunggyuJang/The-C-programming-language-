#include "CharInputSpy.h"
#include <stdio.h>

static const char *fakeStdin;
static int count;

void CharInputSpy_Create(const char *stdin)
{
    fakeStdin = stdin;
    count = 0;
}

void CharInputSpy_Destroy(void)
{
}

int CharInputSpy(void)
{
    count++;
    if (*fakeStdin == '\0')
        return EOF;
    return *fakeStdin++;
}

int CharInputSpy_NumberOfCalled(void)
{
    return count;
}
