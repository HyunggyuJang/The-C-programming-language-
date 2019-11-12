#include <stdio.h>
#include <stdlib.h>             /* for atoi */

#define STARTTAB 2
#define TABSTOP 4

void expandtab(void);
int startTab = 2;               /* default startTab */
int tabstop = 4;            /* default tabstop */
int ncolumn = 0;

int main(int argc, char *argv[]) {
    int c;

    while (--argc > 0)
        switch (c = (*++argv)[0]) {
            case '+':
                tabstop = atoi(++argv[0]);
                break;
            case '-':
                startTab = atoi(++argv[0]);
                break;
            default:
                printf("detab: illegal option \'%s\', instead use default setting\n", argv[0]);
                tabstop = TABSTOP;
                startTab = STARTTAB;
                break;
        }

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

void expandtab(void) {
    putchar(' '), ncolumn++;    /* remove boundary case */
    int distFromStartTab = ncolumn - startTab;
    int remainingSpace =
        (distFromStartTab > 0) ? tabstop - distFromStartTab % tabstop: -distFromStartTab;
    while (remainingSpace-- > 0)
        putchar(' '), ncolumn++;
}
