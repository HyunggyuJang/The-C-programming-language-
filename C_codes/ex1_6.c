#include <stdio.h>



int main() {
    int x;
    x = getchar();
    printf("The input character %c return %d via \"getchar() != EOF\" ", x, x != EOF);
    return 0;
}
