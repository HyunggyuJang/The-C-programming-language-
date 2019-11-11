#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/* getop: get next operator or numeric operand */
int getop(char s[]) {
    int i, c;
    char *t = s;

    while ((*t = c = getch()) == ' ' || c == '\t')
        ;
    *++t = '\0';
    if (!isdigit(c) && c != '.')
        return c;               /* not a number */
    t = s;
    if (isdigit(c))             /* collect integer part */
        while (isdigit(*++t = c = getch()))
            ;
    if (c == '.')               /* collect fractional part */
        while (isdigit(*++t = c = getch()))
            ;
    *t = '\0';
    if (c != EOF)               /* ungetch cannot cope with EOF, which is not in char range */
        ungetch(c);
    return NUMBER;
}
