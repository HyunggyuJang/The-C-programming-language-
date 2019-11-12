#include <stdio.h>
#include <stdlib.h>             /* for atoi */

void dealWithSpace(void);
int getch(void);
void ungetch(int c);

int ncolumn = 0;
int tabstop = 4;


int main(int argc, char *argv[]) {
    int c;

    if (argc > 2) {
        printf("Usage: entab TABSTOP\n");
        return 0;
    }

    if (argc == 2)
        tabstop = atoi(argv[argc - 1]);

    while ((c = getch()) != EOF) {
        switch (c) {
            case ' ':
                dealWithSpace();
                break;
            case '\n':
                putchar('\n');
                ncolumn = 0;
                break;
            default:
                putchar(c);
                ncolumn++;
                break;

        }
    }
}

void dealWithSpace(void) {
    int nentry = ncolumn;       /* store current column position */
    int isblank;               /* the remaining blanks to reach next tab stop */
    int c;
    ++ncolumn;                 /* remove boundary case */
    for (isblank = tabstop - ncolumn % tabstop; isblank && (c = getch()) == ' '; ++ncolumn, --isblank)
        ;
    if (!isblank) {           /* tabstop */
        putchar('\t');
        return;
    }
    while (nentry++ < ncolumn)
        putchar(' ');
    if (c != EOF)
        ungetch(c);             /* overshot */
}
