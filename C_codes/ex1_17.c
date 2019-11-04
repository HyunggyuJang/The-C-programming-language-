#include <stdio.h>
#define INITIALMAX 10
#define TREADHOLD 8

int getlineFrom(int fromIndex, char line[], int maxline);
void printOverflowed(int maxline, char impending[], int isentrypoint);
void copy(char to[], char from[]);
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

void printOverflowed(int oldLim, char impending[], int isentry)
{
    int len;
    int overflow = 0;
    int lim;

    if (isentry)
        lim = oldLim;
    else lim = 2 * oldLim;

    char line[lim];

    if (!isentry) {
        copy(line, impending);
        len = getlineFrom(oldLim - 1, line, lim);
    }

    if (!isentry && isOverflowed(line, len, lim))
        printOverflowed(lim, line, 0);
    else {
        if (!isentry)
            if (len >= TREADHOLD)
                printf("%s", line);
        while ((len = getlineFrom(0, line, lim)) > 0)
            if (isOverflowed(line, len, lim)) {
                overflow = 1;
                printOverflowed(lim, line, 0);
            }
            else if (len >= TREADHOLD)
                printf("%s", line);

    }
}

void copy(char to[], char from[])
{
    int i;
    for (i = 0; (to[i] = from[i]) != '\0'; ++i)
        ;
}

int isOverflowed(char s[], int len, int lim) {
    return (len == lim - 1) && (s[lim - 2] != '\n');
}
