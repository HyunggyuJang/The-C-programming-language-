#include "AllocSpy.h"

static char *startp = 0;
static char *freep = 0;

void AllocSpy_Create(void)
{
    freep = startp = alloc(1);
    afree(startp);
}

void AllocSpy_Destroy(void)
{
    startp = 0;
    freep = 0;
}

char *AllocSpy_alloc(int size)
{
    char *temp = alloc(size);
    if (temp)
        freep = temp + size;
    return temp;
}

static char *inspectCurrentFreePointer(void)
{
    char *temp = alloc(1);
    afree(temp);
    return temp ? temp : freep;
}

void AllocSpy_afree(char *allocated)
{
    afree(allocated);

    freep = inspectCurrentFreePointer();
}

int AllocSpy_AllocatedSpace(void)
{
    return freep - startp;
}
