#include <stdio.h>
#define INITIALMAX 10

int getlineFrom(int fromIndex, char line[], int maxline);
void copy(char to[], char from[]);
void printLongest(int maxline, char impending[]);
int isOverflowed(char line[], int lineLength, int maxline);

main()
{
    int len;
    int max;
    int overflow = 0;
    char line[INITIALMAX];
    char longest[INITIALMAX];

    max = 0;
    while ((len = getlineFrom(0, line, INITIALMAX)) > 0)
        if (isOverflowed(line, len, INITIALMAX)) {
            overflow = 1;
            printLongest(INITIALMAX, line);
        }
        else if (len > max) {
            max = len;
            copy(longest, line);
        }
    if (overflow != 1 && max > 0)
        printf("%s", longest);
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

void printLongest(int oldLim, char impending[])
{
    int len, max;
    int overflow = 0;
    int lim = 2 * oldLim;
    char line[lim];
    char longest[lim];

    copy(line, impending);
    max = len = getlineFrom(oldLim - 1, line, lim);
    if (isOverflowed(line, len, lim))
        printLongest(lim, line);
    else {
        copy(longest, line);
        while ((len = getlineFrom(0, line, lim)) > 0)
            if (isOverflowed(line, len, lim)) {
                overflow = 1;
                printLongest(lim, line);
            }
            else if (len > max) {
                max = len;
                copy(longest, line);
            }
        if (overflow != 1)
            printf("%s", longest);
    }
}

int isOverflowed(char s[], int len, int lim) {
    return (len == lim - 1) && (s[lim - 2] != '\n');
}
