#include <stdio.h>
#define TABSTOP 4               /* Tab stop */
#define FOLD 20                 /* fold point */
#define IN 1
#define OUT 0
#define TRUE 1
#define FALSE 0

/* external variables */
int ncolumn = 0;
char blanks[FOLD] = "";
int bInd = 0;
char word[FOLD] = "";
int wInd = 0;
int state = OUT;
int hasFlushed =  FALSE;
int c;

void updateColumnWhenBlank(char c) {
    if (c == '\t')      /* update ncolumn */
        ncolumn = ncolumn + (TABSTOP - (ncolumn % TABSTOP));
    else ++ncolumn;
}

void updateColumnWhenWord(char c) {
    ++ncolumn;
}

int isWordCharacter(char c) {
    return !(c == ' ' || c == '\t' || c == '\n' || c == EOF);
}

int isBlankCharacter(char c) {
    return (c == ' ' || c == '\t');
}

void flushBlanksIfAny(void) {
    if (bInd > 0) {    /* flush the blanks if any */
        hasFlushed = TRUE;
        printf("%s", blanks);
    }
}

void flushWordIfAny(void) {
    if (wInd > 0) {    /* flush the word if any */
        hasFlushed = TRUE;
        printf("%s", word);
    }
}

void flushAll(void) {
    if (state == IN) {
        flushBlanksIfAny();
        flushWordIfAny();
    } else {
        flushWordIfAny();
        flushBlanksIfAny();
    }
}

void deferBlank(char c) {
    if (bInd > FOLD - 1) {
        char newblanks[2 * FOLD];
        int i;
        for (i = 0; i < FOLD; ++i)
            newblanks[i] = blanks[i];
        blanks = newblanks
    }
    blanks[bInd] = c;
    ++bInd;
}

void deferWord(char c) {
    word[wInd] = c;
    ++wInd;
}

void initializeBlanks(void) {
    bInd = 0;
}

void initializeWord(void) {
    wInd = 0;
}

void initializeColumn(void) {
    initializeBlanks();
    initializeWord();
    hasFlushed = FALSE;
    state = OUT;           /* update state */
    ncolumn = 0;
}

void endOfBlanks(void) {
    blanks[bInd] = '\0';
}

void endOfWord(void) {
    word[wInd] = '\0';
}

void flushAndContinueInNext(void) {
    flushAll();
    initializeColumn();
    putchar('\n');         /* print newline */
    c = getchar();         /* consume one character */
}

void signalFolded(void) {
    putchar('-');
}


int main() {

    c = getchar();
    while (c != EOF) {
        if (ncolumn >= FOLD) {
            if (state == IN) {
                if (!isWordCharacter(c))
                    flushAndContinueInNext();
                else if (hasFlushed) {
                    initializeBlanks();
                    putchar('\n');
                    ncolumn = wInd;
                    hasFlushed = FALSE;
                } else {
                    flushWordIfAny();
                    signalFolded();
                    putchar('\n');
                    initializeColumn();
                }
            } else {
                if (hasFlushed) {
                    flushWordIfAny();
                    if (c == '\n')
                        while (!isWordCharacter(c = getchar()))
                            ;
                    putchar('\n');
                    initializeColumn();
                } else {
                    initializeColumn();
                }
            }
        }
        else if (isBlankCharacter(c)) {
            updateColumnWhenBlank(c);
            flushBlanksIfAny();
            initializeBlanks();
            deferBlank(c);
            while (isBlankCharacter(c = getchar())) { /* consume one more character */
                updateColumnWhenBlank(c);
                deferBlank(c);
            }
            endOfBlanks();
            state = OUT;         /* update state */
        } else if (c == '\n') {
            flushAndContinueInNext();
        } else {                   /* input character is non-blank character */
            updateColumnWhenWord(c);
            flushWordIfAny();
            initializeWord();
            deferWord(c);
            while (isWordCharacter(c = getchar()) && ncolumn < FOLD) {
                updateColumnWhenWord(c);
                deferWord(c);
            }
            endOfWord();
            state = IN;             /* update state */
        }
    }
    flushAll();
    printf("\nThe current column line number is %d", ncolumn);
    return 0;
}
