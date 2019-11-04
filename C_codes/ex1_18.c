#include <stdio.h>
#define INITIALMAX 10
#define TRUE 1

int getlineFrom(int fromIndex, char line[], int maxline);
void printOverflowed(int maxline, char impending[], int isentrypoint);
int isOverflowed(char line[], int lineLength, int maxline);
int removeTrailings(int length, char line[]);
int isWhite(char character);
void copy(char to[], char from[]);

int main()
{
    printOverflowed(INITIALMAX, "", TRUE);
    return 0;
}

int removeTrailings(int len, char s[])
{
    int i = len - 2;
    int newlen;
    if (isWhite(s[i])) {
        s[i+1] = '\0';          /* make the newline character to be null */
        while(i >= 0 && isWhite(s[i])) { /* make sure not to be underflow */
            s[i] = '\0';        /* remove trailing white spaces */
            --i;
        }
        if (i >= 0) {
            ++i;
            s[i] = '\n';      /* restore newline character to be end of new result */
            newlen = i;         /* new length */
        } else
            newlen = 0;
    } else
        newlen = len;
    return newlen;
}

int isWhite(char c) {
    return c == '\t' || c == ' ';
}

void copy(char to[], char from[])
{
    int i;
    for (i = 0; (to[i] = from[i]) != '\0'; ++i)
        ;
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
            if ((len = removeTrailings(len, line)) > 0)
                printf("%s", line);
        while ((len = getlineFrom(0, line, lim)) > 0)
            if (isOverflowed(line, len, lim)) {
                printOverflowed(lim, line, 0);
            }
            else if ((len = removeTrailings(len, line)) > 0)
                printf("%s", line);

    }
}

int isOverflowed(char s[], int len, int lim) {
    return (len == lim - 1) && (s[lim - 2] != '\n');
}
