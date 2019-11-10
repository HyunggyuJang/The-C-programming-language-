#include <stdio.h>
#include <stdlib.h>             /* for atof() */

#define MAXOP 100               /* max size of operand or operator */
#define NUMBER '0'              /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);
void showTop(void);
void duplicate(void);
void swapTops(void);
void initStack(void);
int isInt(double);

/* reverse Polish calculator */
main() {
    int type, intop2;
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
            case '%':
                op2 = pop();
                if (isInt(op2) && (intop2 = op2) && isInt(op2 = pop())) /* integer check & zero check of second argument */
                    push((int) op2 % intop2);
                else
                    printf("error: arguments to moduls are not proper\n");
                break;
            case 't':
                showTop();
                break;
            case 'd':
                duplicate();
                break;
            case 's':
                swapTops();
                break;
            case 'i':
                initStack();
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

void showTop(void) {
    if (sp > 0)
        printf("The top element of stack is %.8g\n", val[sp - 1]);
    else {
        printf("error: stack empty\n");
    }
}

void duplicate(void) {
    if (sp > 0) {
        double temp = pop();
        push(temp);
        push(temp);
    }
    else
        printf("error: stack empty\n");
}

void swapTops(void) {
    if (sp > 1) {
        double temp = pop();
        double temp2 = pop();
        push(temp);
        push(temp2);
    }
    else
        printf("error: stack has less element than 2\n");
}

void initStack(void) {
    sp = 0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    i = 0;                      /* char array to be stored index */

    if (!isdigit(c) && c != '.') {
        if (c != '-' && c != '+')
            return c;           /* not a number */
        else if (isdigit(s[1] = c = getch()))
            i = 2;              /* is number */
        else {
            ungetch(c);         /* push back over consumed character */
            return c = s[0];
        }
    }

    if (isdigit(c))             /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')               /* collect fractional part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)               /* ungetch cannot cope with EOF, which is not in char range */
        ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];              /* buffer for ungetch */
int bufp = 0;                   /* next free position in buf */

int getch(void) {               /* get a (possibly pushed back) character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {           /* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int isInt(double num) {
    int converted = num;
    return (double) converted == num;
}
