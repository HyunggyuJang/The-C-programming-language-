#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);

/* getint: get next integer from input into *pn */
int getint(int *pn) {
    int c, sign = 1;

    while (isspace(c = getch())) /* skip white space */
        ;
    if (!isdigit(c) && c != EOF) { /* ensure c is digit */
        if (c != '+' && c != '-') { /* ensure c is sign token */
            ungetch(c);
            return 0;
        }
        char signExp = c;
        c = getch();            /* lookahead */
        if (!isdigit(c)) {
            if (c != EOF)
                ungetch(c);         /* pushback */
            ungetch(signExp);       /* sign is not number */
            return 0;
        }
        sign = (signExp == '-') ? -1 : 1;
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = *pn * 10 + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

int main(void) {
    int x = 0;
    getint(&x);
    printf("The input stream is integer %d\n", x);
    return 0;
}
