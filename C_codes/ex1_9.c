#include <stdio.h>
int main() {
    int c;
    int flag;
    c = getchar();
    while (c != EOF) {
        flag = 0;               /* mimic if else control structure */
        if (c == ' ') {
            putchar(c);         /* print single blank */
            flag = 1;           /* signal that the entry character was blank */
            while ((c = getchar()) == ' ') /* comsume the successive blanks */
                ;
        }
        if (flag == 0) {        /* if the entry point was non-blank character */
            putchar(c);
            c = getchar();      /* update the c to be consist with comsumption of blanks */
        }
    }
}
