#define ALLOCSIZE 100           /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for allocWrapped */
static char *allocp = allocbuf;  /* next free position */

void calculateWrapped(int n) {
    if (ALLOCSIZE >= n)        /* it fits without additional wrapping */
        allocp += n;
    else
        calculateWrapped(n - ALLOCSIZE + 1); /* need additional wrapping */
}

char *allocWrapped(int n, char *isWrapped) {
    char *returnPointer = allocp;
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits without wrapping */
        allocp += n;
    } else {                    /* should wrap */
        n -= allocbuf + ALLOCSIZE - allocp; /* allocate until end of buffer and wrap */
        *isWrapped = 1;
        allocp = allocbuf;      /* wrapped */
        calculateWrapped(++n);  /* account null character for wrapping */
    }
    return returnPointer;       /* return old pointer */
}


char *firstPointer(void) {
    return allocbuf;
}

char isLastPointer(char *p) {
    return p == allocbuf + ALLOCSIZE - 1;
}
