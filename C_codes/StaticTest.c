#include <stdio.h>

void StaticTest(int x)
{
    static int *test;
    *test = 5;
    printf("%p has value %p, which has value %d\n", &test, test, *test);
    *test = x;                  /* update the test value */
}

int main(void)
{
    int i = 5;
    while (--i > 0)
        StaticTest(i);
    return 0;
}
