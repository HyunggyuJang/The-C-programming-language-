#include <stdio.h>
#include <stdlib.h>             /* for atof() */

#define MAXOP 100               /* max size of operand or operator */
#define NUMBER '0'              /* signal that a number was found */

int getop(char []);
void push (double);
double pop(void);

/* reverse Polish calculator */
main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
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
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

#define MAXVAL 100              /* maximum depth of val stack */

int sp = 0;                     /* next free stack position */
double val[MAXVAL];             /* value stack */

/* push: push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

#include <ctype.h>

int getch(void);
void ungetch(void);

/* getop: get next operator or numeric operand */
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;               /* not a number */
    i = 0;
    if (isdigit(c))             /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')               /* collect fractional part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    ungetch();
    return NUMBER;
}

#define MAXLINE 100

int getLine(char line[], int limit);

char line[MAXLINE];
char linep = -1;                /* to initialize */
int len = -1;                   /* to initialize */

int getch(void) {               /* get a (possibly pushed back) character */
    if (len == 0)               /* End of file */
        return EOF;
    if (linep < len) {
        return line[linep++];
    }
    len = getLine(line, MAXLINE); /* Reach end of line */
    linep = 0;
    return getch();

}

void ungetch(void) {            /* revert the cursor point one character back */
    if (linep > 0)
        linep--;
}

int getLine(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
