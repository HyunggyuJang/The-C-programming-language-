int binsearch(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low < high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid;
    }
    if (v[mid] == x)
        return mid;
    else
        return -1;
}
/* test new binsearch process */
int main(void) {
    int test[10];
    int i;
    for (i = 0; i < 10; ++i)
        test[i] = i;
    i = 3;                      /* test integer */
    printf("the test integer %d found in index %d at test search space",
           i, binsearch(i, test, 10));
    return 0;
}
