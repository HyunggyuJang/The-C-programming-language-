#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);

/* getint: get next integer from input into *pn */
int getfloat(double *pf) {
    int c, sign = 1;
    double power;

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
    for (*pf = 0; isdigit(c); c = getch())
        *pf = *pf * 10 + (c - '0');
    if (c == '.')               /* floating point */
        c = getch();
    for (power = 1.0; isdigit(c); c = getch(), power *= 10.0)
        *pf = *pf * 10 + (c - '0');
    *pf *= sign;
    *pf /= power;
    if (c != EOF)
        ungetch(c);
    return c;
}

int main(void) {
    double x ;
    getfloat(&x);
    printf("The input stream is double %g\n", x);
    return 0;
}
