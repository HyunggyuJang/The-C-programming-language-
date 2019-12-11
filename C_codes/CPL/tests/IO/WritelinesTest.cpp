extern "C"
{
#include "Writelines.h"
#include "FormatOutputSpy.h"
#include <string.h>
#define MAXLINE 30
#define MAXLEN 100
}

#include "CppUTest/TestHarness.h"


TEST_GROUP(Writelines)
{
    char *expectedLines[MAXLINE];
    char expectedWholeLine[MAXLINE * MAXLEN];
    int numberOfLines;
    void setup()
    {
      FormatOutputSpy_Create(MAXLINE * MAXLEN);
      UT_PTR_SET(FormatOutput, FormatOutputSpy);
      memset(expectedLines, NULL, sizeof expectedLines);
      memset(expectedWholeLine, NULL, sizeof expectedLines);
      numberOfLines = 0;
    }
    void teardown()
    {
       FormatOutputSpy_Destroy();
    }
};

TEST(Writelines, WriteNothing)
{
  writelines(expectedLines, 0);
  STRCMP_EQUAL("", FormatOutputSpy_GetOutput());
}

TEST(Writelines, WriteOneLine)
{
  expectedLines[0] = "It can write one line.";
  writelines(expectedLines, 1);
  STRCMP_EQUAL(expectedLines[0], FormatOutputSpy_GetOutput());
}

TEST(Writelines, WriteMultipleLines)
{
  expectedLines[0] = "It can write one line.\n";
  expectedLines[1] = "It can write more line.";

  for (int i = 0; i < 2; ++i)
    strcat(expectedWholeLine, expectedLines[i]);

  writelines(expectedLines, 2);

  STRCMP_EQUAL(expectedWholeLine, FormatOutputSpy_GetOutput());
}
