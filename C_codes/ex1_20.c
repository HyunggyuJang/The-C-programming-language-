#include <stdio.h>
#define TABSTOP 4                     /* Tab stob */

int expandtab(int columnIndex);

int main() {
    int c;
    int ncolumn = 0;

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
    int nextColumn;
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
