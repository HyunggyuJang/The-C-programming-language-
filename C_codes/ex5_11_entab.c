#include <stdio.h>
#include <stdlib.h>             /* for atoi */
int main(int argc, char *argv[]) {
    int c;
    int ncolumn = 0;
    int nexttabstop;
    int nentry;
    int tabstop = 4;            /* default tabstop */

    if (argc > 2) {
        printf("Usage: entab TABSTOP\n");
        return 0;
    }

    if (argc == 2)
        tabstop = atoi(argv[argc - 1]);

    c = getchar();
    while (c != EOF) {
        if (c == ' ') {
            nentry = ncolumn;
            ++ncolumn;
            nexttabstop = ncolumn + (tabstop - (ncolumn % tabstop));
            while (ncolumn != nexttabstop && (c = getchar()) == ' ') {
                ++ncolumn;
            }
            if (ncolumn == nexttabstop) {
                putchar('\t');
                c = getchar();  /* to agree with next branch */
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
            c = getchar();      /* to agree with above if branch */
        }
    }
}
