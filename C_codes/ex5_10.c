#include <stdio.h>
#include <stdlib.h>             /* for atof() */
#include "calc.h"

#define MAXOP 100               /* max size of operand or operator */

int gettype(char *s) {
    if (!isdigit(*s) && *s != '.')
        return *s;              /* not a number */
    return NUMBER;
}

/* reverse Polish calculator */
int main(int argc, char *argv[]) {
    int type;
    double op2;
    char s[MAXOP];

    while (--argc > 0) {
        switch (gettype(*++argv)) {
            case NUMBER:
                push(atof(*argv));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() - op2);
                else
                    printf("error: zero divisor\n");
                break;
            default:
                printf("error: unknown command %s\n", *argv);
                break;
        }
    }
    printf("\t%.8g\n", pop());
    return 0;
}
