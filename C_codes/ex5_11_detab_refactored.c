#include <stdio.h>
#include <stdlib.h>             /* for atoi */

int tabstop = 4;            /* default tabstop */
int ncolumn = 0;

void expandtab(void);

int main(int argc, char *argv[]) {
    int c;

    if (argc > 2) {
        printf("Usage: detab TABSTOP\n");
        return 0;
    }

    if (argc == 2)
        tabstop = atoi(argv[argc - 1]);

    while ((c = getchar()) != EOF) {
        switch(c) {
            case '\t':
                expandtab();
                break;
            case '\n':
                putchar('\n');
                ncolumn = 0;
                break;
            default:
                putchar(c);
                ncolumn++;
        }
    }
}

void expandtab() {
    putchar(' '), ncolumn++;    /* remove boundary case */
    int remainingSpace = tabstop - ncolumn % tabstop;
    while (remainingSpace-- > 0)
        putchar(' '), ncolumn++;
}
