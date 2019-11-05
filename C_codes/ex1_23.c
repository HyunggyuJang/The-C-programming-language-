#include <stdio.h>
#define NORMAL 0
#define SLASH 1
#define INCOMMENT 2
#define ASTERISK 3

int main() {
    int c;
    int state = NORMAL;
    while ((c = getchar()) != EOF) {
        if (state == NORMAL) {
            if (c == '/')
                state = SLASH;
            else putchar(c);    /* copy the input to output */
        }
        else if (state == SLASH) {
            if (c == '*')
                state = INCOMMENT;
            else {
                putchar('/');   /* barfage / */
                putchar(c);     /* copy the input to output */
                state = NORMAL;
            }
        }
        else if (state == INCOMMENT) {
            if (c == '*')
                state = ASTERISK;
        }
        else if (state == ASTERISK) {
            if (c == '/')
                state = NORMAL;
            else state = INCOMMENT;

        }
        else {
            printf("Unknown state %d -- REMOVE_COMMENT", state);
            return 1;           /* error */
        }
    }
    return 0;
}
