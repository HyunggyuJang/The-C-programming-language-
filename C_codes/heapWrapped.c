#define ALLOCSIZE 100           /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for allocWrapped */
static char *allocp = allocbuf;  /* next free position */

char *allocWrapped(int n, char *isWrapped) {
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits without wrapping */
        allocp += n;
        return allocp - n;      /* old p */
    } else {                    /* should wrap */
        n -= allocbuf + ALLOCSIZE - allocp; /* allocate until end of buffer and wrap */
        *isWrapped = 1;
        allocp = allocbuf;      /* wrapped */
        return allocWrapped(++n, isWrapped); /* take account the null character since this string is broken */
    }
}

char *firstPointer(void) {
    return allocbuf;
}

char isLastPointer(char *p) {
    return p == allocbuf + ALLOCSIZE - 1;
}
