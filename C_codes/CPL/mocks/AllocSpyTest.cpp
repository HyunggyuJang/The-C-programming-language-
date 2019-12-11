extern "C"
{
#include "AllocSpy.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(AllocSpy)
{
  void setup()
  {
    UT_PTR_SET(charAlloc, AllocSpy_alloc);
    UT_PTR_SET(freeChar, AllocSpy_afree);
    areset();
    AllocSpy_Create();
  }

  void teardown()
  {
    AllocSpy_Destroy();
  }
};

TEST(AllocSpy, Create)
{
  LONGS_EQUAL(0, AllocSpy_AllocatedSpace());
}

TEST(AllocSpy, CanInspectAllocatedSpaceAtOneCall)
{
  charAlloc(5);
  LONGS_EQUAL(5, AllocSpy_AllocatedSpace());
}

TEST(AllocSpy, CanInspectAllocatedSpaceWithMultipleCall)
{
  charAlloc(5);
  charAlloc(3);
  LONGS_EQUAL(8, AllocSpy_AllocatedSpace());
}

TEST(AllocSpy, CopeWithInterwovenFreeCalls)
{
  charAlloc(5);
  char *allocated = charAlloc(3);

  freeChar(allocated);
  LONGS_EQUAL(5, AllocSpy_AllocatedSpace());
}

TEST(AllocSpy, CopeWithBoundaryAllocation)
{
  charAlloc(ALLOCSIZE);

  LONGS_EQUAL(ALLOCSIZE, AllocSpy_AllocatedSpace());
}

TEST(AllocSpy, CopeWithOverflowedAllocation)
{
  charAlloc(5);
  charAlloc(ALLOCSIZE);

  LONGS_EQUAL(5, AllocSpy_AllocatedSpace());
}

TEST(AllocSpy, CopeWithOverflowedBoundaryAllocation)
{
  charAlloc(ALLOCSIZE);
  charAlloc(1);

  LONGS_EQUAL(ALLOCSIZE, AllocSpy_AllocatedSpace());
}

TEST(AllocSpy, CopeWithInvalidFree)
{
  char *allocated = charAlloc(3);
  freeChar(allocated - 1);

  LONGS_EQUAL(3, AllocSpy_AllocatedSpace());
}
