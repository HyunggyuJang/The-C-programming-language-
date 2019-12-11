extern "C"
{
#include "QuickSort.h"
#include <memory.h>
}

#include "CppUTest/TestHarness.h"
#define ARRAYLEN 10

TEST_GROUP(QuickSort)
{
  int *unsorted[ARRAYLEN];
  int *toBeSorted[ARRAYLEN];

    void setup()
    {
      memset(unsorted, NULL, sizeof unsorted);
    }

    void teardown()
    {
    }

    void copyFromUnsortedToBeSorted()
    {
      for (int i = 0; i < ARRAYLEN; ++i)
        toBeSorted[i] = unsorted[i];
    }

};

int intComp(int *ip, int *jp)
{
  if (*ip > *jp)
    return 1;
  if (*ip < *jp)
    return -1;
  return 0;
}

TEST(QuickSort, NoElementToSort)
{
  copyFromUnsortedToBeSorted();

  quickSort((void **) toBeSorted, 0, 0,
        (int (*)(void *, void *)) intComp);

  for (int i = 0; i < ARRAYLEN; ++i)
    POINTERS_EQUAL(unsorted[i], toBeSorted[i]);
}

TEST(QuickSort, OneElementToSort)
{
  int i = 2;
  unsorted[0] = &i;

  copyFromUnsortedToBeSorted();

  quickSort((void **) toBeSorted, 0, 0,
        (int (*)(void *, void *)) intComp);

  for (int j = 0; j < ARRAYLEN; ++j)
    POINTERS_EQUAL(unsorted[j], toBeSorted[j]);
}

TEST(QuickSort, CanSwap)
{
  int i = 5;
  int j = 2;
  toBeSorted[0] = &i;
  toBeSorted[1] = &j;

  swap((void **) toBeSorted, 0, 1);

  LONGS_EQUAL(2, *toBeSorted[0]);
  LONGS_EQUAL(5, *toBeSorted[1]);
}

TEST(QuickSort, CanSortArbitraryNumberOfElement)
{
  int i, unsortedInts[6] = {5, 3, 2, 1, 6, 4};
  for (i = 0; i < 6; ++i)
    unsorted[i] = unsortedInts + i;

  copyFromUnsortedToBeSorted();

  quickSort((void **) toBeSorted, 0, 5,
        (int (*)(void *, void *)) intComp);

  for (i = 0; i < 6; i++)
    LONGS_EQUAL(i + 1, *toBeSorted[i]);
}
