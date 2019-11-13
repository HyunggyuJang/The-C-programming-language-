#define MAXLEN 20
#include "ex5_13.h"

int isOverflowed(char *, int, int);
int getLine(char *, int);

int
readLineWrappedN()
{
    char line[MAXLEN];          /* current input line */
    int len;
    char overflowed = 0;
    char shouldInsert;
    char isWrapped = 0;
    char *p;
    while ((len = getLine(line, MAXLEN)) > 0)
    {
        shouldInsert = !overflowed;
        if ((overflowed = isOverflowed(line, len, MAXLEN)))
            len -= 1;           /* remove last null character to link with next */
        else if (line[len - 1] == '\n')        /* not last line */
            line[--len] = '\0'; /* remove newline character */
        isWrapped = 0;          /* initialize isWrapped */
        p = allocWrapped(len + 1, &isWrapped); /* install until null character */
        if (shouldInsert)
            insertLast(p, isWrapped);
        installWrapped(p, line, len + 1); /* install until null character */
    }
    if (existDestroyed())
        return ERROR;
    return SUCCESS;
}

int isOverflowed(char s[], int len, int lim) {
    return (len == lim - 1) && (s[lim - 2] != '\n');
}
