#include <stdio.h>






int main() {

int c, flag;


while ((c = getchar ()) != EOF) {
    flag = 1;
    if (c == '\b') {
        flag = 0;
        printf("\\b");
    }
    if (c == '\t') {
        flag = 0;
        printf("\\t");
    }
    if (c == '\n') {
        flag = 0;
        printf("\\n");
    }
    if (c == '\\') {
        flag = 0;
        printf("\\\\");
    }
    if (flag)
        putchar(c);
}
return 0;
}
