#include <stdio.h>
#define IN 1
#define OUT 0





int main() {
int c, state;

state = OUT;
while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t') {
        if (state == OUT)
            ;                   /* ignore the input character */
        else {
            state = OUT;
            putchar('\n');
        }
    }
    else {
        state = IN;
        putchar(c);
    }
}
return 0;
}
