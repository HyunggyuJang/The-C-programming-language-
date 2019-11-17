/* qsort: sort v[left]...v[right] into increasing order */
void qsort(void *v[], int left, int right,
           int (*comp)(void *, void *)) {
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)          /* do nothing if array contains */
        return;                 /* fewer than two elements */
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1, comp);
    qsort(v, last + 1, right, comp);
}

#include <string.h>
#include <stdio.h>
#include <assert.h>

void swap(void *v[], int i, int j) {
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* test qsort */
int main(void) {
    char *test[] = {"9", "7", "8", "5", "2", "6", "3", "4", "1"};
    int len = 9;
    char temp[len];
    qsort((void **) test, 0, len - 1, (int (*)(void *, void *)) strcmp); /* sort */
    while (len-- > 0) {
        sprintf(temp, "%d", len + 1);
        assert(strcmp(temp ,test[len]) == 0); /* test[i] == i + 1 */
    }
}
