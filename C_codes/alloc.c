#define ALLOCSIZE 10000         /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */

char *alloc(int n) {            /* return pointer to n characters */
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
        allocp += n;
        return allocp - n;       /* old p */
    } else                      /* not enough room */
        return 0;
}

void afree(char *p) {           /* free storage pointed to by p */
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

#include <assert.h>
#include <string.h>
/* testing alloc and free */
int main_(void) {
    int n = 10;
    assert(allocp == allocbuf);        /* before allocating any, it should be initialzied */

    char *teststring = alloc(n);
    assert(teststring == allocbuf); /* the old pointer is bound to newly allocated data */

    assert(allocp == allocbuf + n); /* after allocating n blocks, it should point to next free pointer */
    strcpy(teststring, "123456789"); /* exactly n = 10 block size */

    char *testAlloc = alloc(n);     /* new allocating */
    assert(strcmp(teststring, "123456789") == 0); /* after allocating it should retain previosly allocated one */

    assert(allocp == allocbuf + 2*n); /* before freeing the current pointer */
    /* freeing */
    afree(testAlloc);
    assert(allocp == allocbuf + n); /* the last one freed */

    afree(teststring);
    assert(allocp == allocbuf);    /* reverted to initial pointer */
    char *testLast = alloc(n);  /* make garbages */
    strcpy(testLast, "987654321");                /* destroyed garbage */
    assert(strcmp(teststring, "123456789") != 0); /* the previous one destructed */
}
