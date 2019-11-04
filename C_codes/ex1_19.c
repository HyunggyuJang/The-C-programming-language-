#include <stdio.h>
#define INITIALMAX 10
#define TRUE 1

int getlineFrom(int fromIndex, char line[], int maxline);
void printOverflowed(int maxline, char impending[], int isentrypoint);
int isOverflowed(char line[], int lineLength, int maxline);
void reverse(int length, char line[]);
void copy(char to[], char from[]);

int main()
{
    printOverflowed(INITIALMAX, "", TRUE);
    return 0;
}

void reverse(int len, char s[])
{
    int lastIndex = len - 2;    /* lastIndex except the newline character */
    int halfIndex = (lastIndex - 1) / 2; /* use integer division to be used in loop */
    char temp;                           /* temporary storage to interchange */
    int i;                               /* loop index */
    for (i = 0; i <= halfIndex; ++i) {
        temp = s[i];
        s[i] = s[lastIndex - i];
        s[lastIndex - i] = temp;
    }
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
        if (!isentry) {
            reverse(len, line);
            printf("%s", line);
        }
        while ((len = getlineFrom(0, line, lim)) > 0)
            if (isOverflowed(line, len, lim)) {
                printOverflowed(lim, line, 0);
            }
            else {
                reverse(len, line);
                printf("%s", line);
            }

    }
}

int isOverflowed(char s[], int len, int lim) {
    return (len == lim - 1) && (s[lim - 2] != '\n');
}
