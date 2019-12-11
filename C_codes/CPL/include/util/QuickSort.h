#ifndef D_QuickSort_H
#define D_QuickSort_H

/**********************************************************
 *
 * QuickSort is responsible for ...
 *
 **********************************************************/

void quickSort(void *v[], int left, int right,
           int (*comp)(void *, void *));

void swap(void *v[], int, int);

#endif  /* D_FakeQuickSort_H */
