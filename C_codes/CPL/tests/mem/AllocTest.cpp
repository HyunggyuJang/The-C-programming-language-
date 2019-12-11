extern "C"
{
#include "Alloc.h"
#include "string.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Alloc)
{
  char *allocated;
    void setup()
    {
      areset();
      allocated = alloc(10);
    }

    void teardown()
    {
      afree(allocated);
    }
};

TEST(Alloc, AllocAndFree)
{
  afree(allocated);

  char *reallocated = alloc(5);

  POINTERS_EQUAL(reallocated, allocated);

  afree(reallocated);
}

TEST(Alloc, AllocateSize)
{
  allocated = alloc(5);
  char *moreAllocated = alloc(5);

  POINTERS_EQUAL(allocated + 5, moreAllocated);

  afree(moreAllocated);
  afree(allocated);
}

TEST(Alloc, AllocateAndRetrieve)
{
  strcpy(allocated, "1234");
  alloc(32);
  STRCMP_EQUAL(allocated, "1234");
}

TEST(Alloc, AllocLeadsOverFlow)
{
  char *overflowedAllocation = alloc(ALLOCSIZE);
  POINTERS_EQUAL(overflowedAllocation, NULL);
}

TEST(Alloc, FreeUnderflow)
{
  afree(allocated - 1);
  char *moreAllocated = alloc(5);
  POINTERS_EQUAL(moreAllocated, allocated + 10);
}

TEST(Alloc, FreeOverflow)
{
  afree(allocated + ALLOCSIZE);
  char *moreAllocated = alloc(5);
  POINTERS_EQUAL(moreAllocated, allocated + 10);
}
