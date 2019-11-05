#include <stdio.h>
#define TABSTOP 4               /* Tab stop */
#define FOLD 20                 /* fold point */
#define IN 1
#define OUT 0

int updateWhenBlank(char c, int ncolumn) {
    if (c == '\t')      /* update ncolumn */
        ncolumn = ncolumn + (TABSTOP - (ncolumn % TABSTOP));
    else ++ncolumn;
    return ncolumn;
}

int isWordCharacter(char c) {
    return !(c == ' ' || c == '\t' || c == '\n' || c == EOF);
}

int isBlankCharacter(char c) {
    return (c == ' ' || c == '\t');
}

int main() {
    int c;
    int ncolumn = 0;
    char blanks[FOLD] = "";
    int bInd = 0;
    char word[FOLD] = "";
    int wInd = 0;
    int state = OUT;

    c = getchar();
    while (c != EOF) {
        if (isBlankCharacter(c)) {
            ncolumn = updateWhenBlank(c, ncolumn);
            if (bInd > 0) {     /* flush the blanks if any */
                printf("%s", blanks);
                bInd = 0;
            }
            blanks[bInd] = c;   /* defer input character */
            ++bInd;             /* update next Index of blanks */
            while (isBlankCharacter(c = getchar())) { /* consume one more character */
                ncolumn = updateWhenBlank(c, ncolumn);
                blanks[bInd] = c;   /* defer input character */
                ++bInd;             /* update next Index of blanks */
            }
            blanks[bInd] = '\0'; /* the end of string character */
            state = OUT;         /* update state */
        } else if (c == '\n') {
            if (state == IN) {
                if (bInd > 0)
                    printf("%s", blanks);
                if (wInd > 0)
                    printf("%s", word);
            } else {
                if (wInd > 0)
                    printf("%s", word);
                if (bInd > 0)
                    printf("%s", blanks);
            }
            bInd = 0;
            wInd = 0;
            ncolumn = 0;
            putchar('\n');         /* print newline */
            state = OUT;           /* update state */
            c = getchar();         /* consume one character */
        } else {                   /* input character is non-blank character */
            ++ncolumn;             /* update column line number */
            if (wInd > 0) {        /* flush word */
                printf("%s", word);
                wInd = 0;
            }
            word[wInd] = c;     /* defer current character */
            ++wInd;             /* update the word Index */
            while (isWordCharacter(c = getchar())) {
                ++ncolumn;      /* update column line number */
                word[wInd] = c;     /* defer current character */
                ++wInd;             /* update the word Index */
            }
            word[wInd] = '\0';  /* end of string */
            state = IN;             /* update state */
        }
    }
    if (state == IN) {
        if (bInd > 0)
            printf("%s", blanks);
        if (wInd > 0)
            printf("%s", word);
    } else {
        if (wInd > 0)
            printf("%s", word);
        if (bInd > 0)
            printf("%s", blanks);
    }
    return 0;
}
