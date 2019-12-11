extern "C"
{
#include "CharInputSpy.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(CharInputSpy)
{
  int charGot;

  void setup()
  {
    UT_PTR_SET(CharInput, CharInputSpy);
  }

  void teardown()
  {
    CharInputSpy_Destroy();
  }
};

TEST(CharInputSpy, CreateWithNothing)
{
  CharInputSpy_Create("");

  charGot = CharInput();

  LONGS_EQUAL(EOF, charGot);
}

TEST(CharInputSpy, CreateWithOneCharacter)
{
  CharInputSpy_Create("a");

  charGot = CharInput();
  LONGS_EQUAL('a', charGot);
}

TEST(CharInputSpy, CheckTheNumberOfCalled)
{
  int nCalled = 5;
  CharInputSpy_Create("");

  for (int i = 0; i < nCalled; ++i)
  {
    CharInputSpy();
  }

  LONGS_EQUAL(nCalled,
              CharInputSpy_NumberOfCalled());
}

TEST(CharInputSpy, CreateWithMultipleCharacters)
{
  const char *multiChars = "abcd";
  CharInputSpy_Create(multiChars);

  while((charGot = CharInput()) != EOF)
  {
    LONGS_EQUAL(*multiChars++, charGot);
  }
}
