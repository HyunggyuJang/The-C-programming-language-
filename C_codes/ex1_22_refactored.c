#include <stdio.h>
#define TABSTOP 4               /* Tab stop */
#define FOLD 20                 /* fold point */
#define IN 1
#define OUT 0

/* external variables */
int ncolumn = 0;
char blanks[FOLD] = "";
int bInd = 0;
char word[FOLD] = "";
int wInd = 0;
int state = OUT;

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
    if (bInd > 0)      /* flush the blanks if any */
        printf("%s", blanks);
}

void flushWordIfAny(void) {
    if (wInd > 0)      /* flush the word if any */
        printf("%s", word);
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
    ncolumn = 0;
}

void endOfBlanks(void) {
    blanks[bInd] = '\0';
}

void endOfWord(void) {
    word[wInd] = '\0';
}

int main() {
    int c;

    c = getchar();
    while (c != EOF) {
        if (isBlankCharacter(c)) {
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
            flushAll();
            initializeBlanks();
            initializeWord();
            initializeColumn();
            putchar('\n');         /* print newline */
            state = OUT;           /* update state */
            c = getchar();         /* consume one character */
        } else {                   /* input character is non-blank character */
            updateColumnWhenWord(c);
            flushWordIfAny();
            initializeWord();
            deferWord(c);
            while (isWordCharacter(c = getchar())) {
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
