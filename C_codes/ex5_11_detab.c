#include <stdio.h>
#include <stdlib.h>             /* for atoi */
#define TABSTOP 4                     /* Tab stop */

int expandtab(int columnIndex);

int main(int argc, char *argv[]) {
    int c;
    int ncolumn = 0;
    int tabstop = 4;            /* default tabstop */

    if (argc > 2) {
        printf("Usage: detab TABSTOP\n");
        return 0;
    }

    if (argc == 2)
        tabstop = atoi(argv[argc - 1]);

    while ((c = getchar()) != EOF) {
        if (c == '\t')
            ncolumn = expandtab(ncolumn); /* update column number */
        else {
            putchar(c);
            if (c == '\n')
                ncolumn = 0;    /* initialize column number */
            else ++ncolumn;     /* increase column number */
        }
    }
}

int expandtab(int nc) {
    if ((nc % TABSTOP) == 0) {
        putchar(' ');
        ++nc;
    }
    while((nc % TABSTOP) != 0) {
        putchar(' ');
        ++nc;
    }
    return nc;
}
