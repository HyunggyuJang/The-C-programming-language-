#include <stdio.h>

#define START 0
#define INCOMMENT 1
#define MAXIMUMDEPTH 1000

/* external varaible -- static stack */
char stack[MAXIMUMDEPTH];
int sp = 0;                     /* current stack point */

int isEmptyStack(void) {
    return sp == 0;
}

char pop(void) {
    --sp;
    return stack[sp];
}

void push(char c) {
    stack[sp] = c;
    ++sp;
}

int error(char c) {
    printf("Unexpected character %c encountered", c);
    return 0;
}

int isOpeningQuote(char c) {
    return c == '\'' || c == '"';
}

int isOpeningNestable(char c) {
    return c == '{' || c == '[' || c == '(';
}

int isClosingNestable(char c) {
    return c == '}' || c == ']' || c == ')';
}

int isTransientOpeningComment(char c) {
    return c == '/';
}

int isOpeningEscape(char c) {
    return c == '\\';
}

int isTransientClosingComment(char c) {
    return c == '*';
}

int isMatched(char o, char c) {
    if (o == '{')
        return c == '}';
    else if (o == '(')
        return c == ')';
    else if (o == '[')
        return c == ']';
    else if (isOpeningQuote(o))
        return c == o;
    else
        return 0;
}

int main() {
    int c = getchar();
    int state = START;
    while (c != EOF) {
        if (state == START) {
            if (isOpeningQuote(c) || isOpeningNestable(c) || isTransientOpeningComment(c))
                state = c;

            else if (isOpeningEscape(c)){
                return error(c);
            }
            c = getchar();
        }
        else if (isTransientOpeningComment(state)) { /* no consumption of character just set the state */
            if (c == '*')
                state = INCOMMENT;
            else {
                if (isEmptyStack())
                    state = START;
                else
                    state = pop();
            }
        }
        else if (isTransientClosingComment(state)) { /* same as above since these are transient state */
            if (c == '/') {
                if (isEmptyStack())
                    state = START;
                else
                    state = pop();
            }
            else
                state = INCOMMENT;
        }
        else if (state == INCOMMENT) {
            if (isTransientClosingComment(c))
                state = c;
            c = getchar();
        }
        else if (isOpeningNestable(state)) {
            if (isOpeningNestable(c) || isOpeningQuote(c) || isTransientOpeningComment(c)) {
                push(state);    /* Push current state to stack */
                state = c;      /* update current */
            }
            else if (isMatched(state, c)) {
                if (isEmptyStack())
                    state = START;
                else
                    state = pop(); /* Pop from current stack if not empty */
            }
            else if (isOpeningEscape(c) || isClosingNestable(c)) {
                return error(c);
            }
            c = getchar();
        }
        else if (isOpeningQuote(state)) {
            if (isMatched(state, c)) {
                if (isEmptyStack())
                    state = START;
                else
                    state = pop(); /* Pop from current stack if not empty */
            }
            else if (isOpeningEscape(c)) {
                if ((c = getchar()) == EOF) {
                    return error(c);
                }
            }
            c = getchar();
        }
        else                    /* defensive programming */
            return error(c);
    }
    if (!isEmptyStack()) {
        stack[sp + 1] = '\0';       /* for printing */
        printf("The stacked nestables are unmatched %s", stack);
    }
    return 0;
}
