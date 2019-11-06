#include <stdio.h>






int main() {
int c, i, j;
int length = 'z' - 'a' + 1;
int nchars[length];

for (i = 0; i < length; ++i)
    nchars[i] = 0;

while ((c = getchar()) != EOF) {
    if ('a' <= c && c <= 'z')
        ++nchars[c - 'a'];
}

printf("%s\t%s\n", "Character", "Frequency");
for (i = 0; i < length; ++i) {
    if (nchars[i] != 0) {       /* print only non zero frequency entries */
        printf("%c\t", i + 'a');
        for (j = 0; j < nchars[i]; ++j) /* print histogram which represent frequency */
            putchar('*');
        putchar('\n');
    }
}
return 0;
}
