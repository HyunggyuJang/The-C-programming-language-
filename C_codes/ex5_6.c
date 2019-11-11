#include <stdio.h>
#include <ctype.h>






int getLine(char *s, int lim) {
    int c;
    int tLim = lim;
    while (lim > 1 && (c = getchar()) != EOF && c != '\n')
        *s++ = c, lim--;
    if (c == '\n')
        *s++ = c, lim--;
    *s = '\0';
    return tLim - lim;
}

void reverse(char *s) {
    char *t = s + strlen(s) - 1;
    char temp;
    while (s < t)
        temp = *s, *s++ = *t, *t-- = temp;
}

int atoi(char *s) {
    int n = 0;
    if (isspace(*s))
        while (isspace(*s++))
            ;
    --s;                        /* revert one overshot */
    while (isdigit(*s))
        n = 10 * n + (*s++ - '0');
    return n;
}

void itoa(int n, char *s) {
    int sign;
    char *t = s;
    if ((sign = n) < 0)
        n = -n;
    do {
        *s++ = n % 10 + '0';
    }
    while ((n /= 10) > 0);
    if (sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse(t);                 /* reverse the whole string */
}

int strindex(char *s, char *t) {
    char *u, *v, *w;            /* moving pointers */
    for (w = s; *w != '\0'; w++) {
        for (u = w, v = t; *u != '\0' && *u++ == *v++;)
            ;
        if ((v - t) && *v == '\0')
            return w - s;
    }
    return -1;
}

int main(void) {
    char test[20];
    getLine(test, 20);
    printf("%s got from getLine\n", test);
    reverse(test);
    printf("and got revered as %s\n", test);
    int testInt = atoi(test);
    printf("Now it transformed as int %d\n", testInt);
    itoa(testInt, test);
    printf("It reverted back as %s\n", test);
    char test2[20];
    getLine(test2, 20);
    printf("Then %s occurs at %d in %s", test2, strindex(test, test2), test);
    return 0;
}
