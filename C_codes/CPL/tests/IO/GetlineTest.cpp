extern "C"
{
#include "Getline.h"
#include "CharInputSpy.h"
#include <memory.h>
#include <stdio.h>
#include <string.h>
}

#include "CppUTest/TestHarness.h"
#define LIMIT 21

TEST_GROUP(Getline)
{
  int nChars;
  char lineRead[LIMIT + 20];
  char expected[LIMIT + 20];

  void setup()
  {
      UT_PTR_SET(CharInput, CharInputSpy);
      memset(lineRead, 0xff, sizeof lineRead);
  }

  void teardown()
  {
      CharInputSpy_Destroy();
  }

  void checkReadWithExpected()
  {
      LONGS_EQUAL(strlen(expected), nChars);
      STRCMP_EQUAL(expected, lineRead);
  }
};

TEST(Getline, OnlyEndOfChacter)
{
    sprintf(expected, "\n");
    CharInputSpy_Create(expected);
    nChars = getLine(lineRead, LIMIT);

    checkReadWithExpected();
    LONGS_EQUAL(1,
                CharInputSpy_NumberOfCalled());
}

TEST(Getline, ReadNewlineCharacter)
{
    sprintf(expected, "\n");
    CharInputSpy_Create(expected);
    nChars = getLine(lineRead, LIMIT);

    checkReadWithExpected();
    LONGS_EQUAL(1,
                CharInputSpy_NumberOfCalled());
}

TEST(Getline, ReadOneCharacterAndEOF)
{
    sprintf(expected, "a");
    CharInputSpy_Create(expected);
    nChars = getLine(lineRead, LIMIT);

    checkReadWithExpected();
    LONGS_EQUAL(2,
                CharInputSpy_NumberOfCalled());
}

TEST(Getline, DoNotReadOverEOF)
{
    *expected = '\0';
    sprintf(expected + 1, "Shouldn't be read");
    CharInputSpy_Create(expected);
    nChars = getLine(lineRead, LIMIT);

    checkReadWithExpected();
    LONGS_EQUAL(1,
                CharInputSpy_NumberOfCalled());
}

TEST(Getline, DoNotReadOverNewline)
{
    *expected = '\n';
    sprintf(expected + 1, "Shouldn't be read");
    CharInputSpy_Create(expected);
    nChars = getLine(lineRead, LIMIT);

    expected[0] = '\n';
    expected[1] = '\0';

    checkReadWithExpected();
    LONGS_EQUAL(1,
                CharInputSpy_NumberOfCalled());
}

TEST(Getline, CanReadLessThanLimitEndsWithEOF)
{
    sprintf(expected, "This should be read");
    CharInputSpy_Create(expected);
    nChars = getLine(lineRead, LIMIT);

    checkReadWithExpected();
    LONGS_EQUAL(strlen(expected) + 1,
                CharInputSpy_NumberOfCalled());
}

TEST(Getline, CanReadLessThanLimitEndsWithNewline)
{
    sprintf(expected, "This should be read\n");
    CharInputSpy_Create(expected);
    nChars = getLine(lineRead, LIMIT);

    checkReadWithExpected();
    LONGS_EQUAL(strlen(expected),
                CharInputSpy_NumberOfCalled());
}

TEST(Getline, CannotReadOverLimitation)
{
    sprintf(expected, "This should be read. But it shouldn't");
    CharInputSpy_Create(expected);
    nChars = getLine(lineRead, LIMIT);

    expected[LIMIT - 1] = '\0';

    checkReadWithExpected();
    LONGS_EQUAL(LIMIT - 1,
                CharInputSpy_NumberOfCalled());
}

TEST(Getline, CanCallSuccessively)
{
    sprintf(expected, "This should be read. It shouldn't in one");
    CharInputSpy_Create(expected);
    nChars = getLine(lineRead, LIMIT);
    nChars += getLine(lineRead + LIMIT - 1, LIMIT);

    checkReadWithExpected();
    LONGS_EQUAL(strlen(expected),
                CharInputSpy_NumberOfCalled());
}
