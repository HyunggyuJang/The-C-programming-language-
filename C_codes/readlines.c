#include <string.h>
#include <stdio.h>

#define MAXLEN 1000             /* max length of any input line */
int getLine(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getLine(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

int main_(void) {
    int maxlines = 100;
    /* spit out what it read */
    char *lineptr[maxlines];

    int nlines = readlines(lineptr, maxlines);
    writelines(lineptr, nlines);
    return 0;
}
