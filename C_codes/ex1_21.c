#include <stdio.h>
#define TABSTOP 4               /* Tab stop */

int main() {
    int c;
    int ncolumn = 0;
    int nexttabstop;
    int nentry;

    c = getchar();
    while (c != EOF) {
        if (c == ' ') {
            nentry = ncolumn;
            ++ncolumn;
            nexttabstop = ncolumn + (TABSTOP - (ncolumn % TABSTOP));
            while ((c = getchar()) == ' ' && ncolumn != nexttabstop) {
                ++ncolumn;
            }
            if (ncolumn == nexttabstop) {
                putchar('\t');
            } else {
                while(nentry != ncolumn) {
                    putchar(' ');
                    ++nentry;
                }
            }
        } else {
            putchar(c);
            if (c == '\n')
                ncolumn = 0;
            else ++ncolumn;
            c = getchar();
        }
    }
}
