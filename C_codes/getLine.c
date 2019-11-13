#include <stdio.h>

int getLine(char *s, int lim) {
    int c;
    int tLim = lim;
    while (lim > 1 && (c = getchar()) != EOF && c != '\n')
        *s++ = c, lim--;
    if (c == '\n')
        *s++ = c, lim--;
    *s = '\0';
    return tLim - lim;
}
