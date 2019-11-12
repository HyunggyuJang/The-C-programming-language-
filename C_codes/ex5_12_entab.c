#include <stdio.h>
#include <stdlib.h>             /* for atoi */

#define TABSTOP 4
#define STARTTAB 2

void dealWithSpace(void);
int getch(void);
void ungetch(int c);

int ncolumn = 0;
int tabstop = TABSTOP;
int startTab = STARTTAB;


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
                printf("entab: illegal option \'%s\', instead use default setting\n", argv[0]);
                tabstop = TABSTOP;
                startTab = STARTTAB;
                break;
        }

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
    int nentry = ncolumn++;       /* store current column position */
    int isblank;               /* the remaining blanks to reach next tab stop */
    int c;
    int distFromStartTab = ncolumn - startTab;

    for (isblank = (distFromStartTab > 0) ? tabstop - distFromStartTab % tabstop : -distFromStartTab;
         isblank && (c = getch()) == ' '; ++ncolumn, --isblank)
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
