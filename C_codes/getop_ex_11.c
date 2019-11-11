#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/* getop: get next operator or numeric operand */
int getop(char s[]) {
    int i, c;
    static char pushbacked = '\0';
    static char hasPushbacked = 0;

    while ((s[0] = c = (hasPushbacked ? (hasPushbacked = 0, pushbacked) : getchar())) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;               /* not a number */
    i = 0;
    if (isdigit(c))             /* collect integer part */
        while (isdigit(s[++i] = c = (hasPushbacked ? (hasPushbacked = 0, pushbacked) : getchar())))
            ;
    if (c == '.')               /* collect fractional part */
        while (isdigit(s[++i] = c = (hasPushbacked ? (hasPushbacked = 0, pushbacked) : getchar())))
            ;
    s[i] = '\0';
    if (c != EOF)               /* ungetch cannot cope with EOF, which is not in char range */
        hasPushbacked = 1, pushbacked = c;
    return NUMBER;
}
