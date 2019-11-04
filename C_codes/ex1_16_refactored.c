#include <stdio.h>
#define INITIALMAX 10

int getlineFrom(int fromIndex, char line[], int maxline);
void copy(char to[], char from[]);
void printOverflowed(int maxline, char impending[], int isentrypoint);
int isOverflowed(char line[], int lineLength, int maxline);

main()
{
    printOverflowed(INITIALMAX, "", 1);
    return 0;
}

int getlineFrom(int from, char s[], int lim)
{
    int c, i;
    for (i = from; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void copy(char to[], char from[])
{
    int i;
    for (i = 0; (to[i] = from[i]) != '\0'; ++i)
        ;
}

void printOverflowed(int oldLim, char impending[], int isentry)
{
    int len, max;
    int overflow = 0;
    int lim;
    char line[lim];
    char longest[lim];

    if (isentry) {
        lim = oldLim;
        max = 0;
    }
    else {
        lim = 2 * oldLim;
        copy(line, impending);
        max = len = getlineFrom(oldLim - 1, line, lim);
    }

    if (!isentry && isOverflowed(line, len, lim))
        printOverflowed(lim, line, 0);
    else {
        if (!isentry)
            copy(longest, line);
        while ((len = getlineFrom(0, line, lim)) > 0)
            if (isOverflowed(line, len, lim)) {
                overflow = 1;
                printOverflowed(lim, line, 0);
            }
            else if (len > max) {
                max = len;
                copy(longest, line);
            }
        if (!overflow && (!isentry || (isentry && max > 0)))
            printf("%s", longest);
    }
}

int isOverflowed(char s[], int len, int lim) {
    return (len == lim - 1) && (s[lim - 2] != '\n');
}
