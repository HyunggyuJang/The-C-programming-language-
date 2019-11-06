#include <stdio.h>
#define IN 1
#define OUT 0
#define MAX_LENG 100





int main() {

int c, i, j, wl, state;
int nwords[MAX_LENG];

state = OUT;
wl = 0;
for (i = 0; i < MAX_LENG; ++i)
    nwords[i] = 0;

while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t') {
        if (state == IN)        /* IN -> OUT transition */
            ++nwords[wl];

        state = OUT;
    }
    else {
        if (state == OUT)       /* OUT -> IN transition */
            wl = 0;             /* initialize word length counter */
        state = IN;
        ++wl;
    }
}

if (state == IN)                /* EOF is also delimiter */
    ++nwords[wl];

printf("%s\t%s\n", "Word length", "Frequency");
for (i = 0; i < MAX_LENG; ++i) {
    if (nwords[i] != 0) {       /* print only non zero frequency entries */
        printf("%d\t", i);
        for (j = 0; j < nwords[i]; ++j) /* print histogram which represent frequency */
            putchar('*');
        putchar('\n');
    }
}
return 0;
}
