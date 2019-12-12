extern "C"
{
#include "SortLines.h"
#include "CharInputSpy.h"
#include "FormatOutputSpy.h"
#include <stdio.h>
#include <stdarg.h>
}

#include "CppUTest/TestHarness.h"
#define INPUTLEN MAXLINES * 10

TEST_GROUP(SortLines)
{
  char *fakeInput;
  int offset;
  int result;
    void setup()
    {
      fakeInput = (char *) malloc(MAXLINES * 10);
      offset = 0;
      UT_PTR_SET(CharInput, CharInputSpy);
      UT_PTR_SET(FormatOutput, FormatOutputSpy);
      FormatOutputSpy_Create(INPUTLEN);
      CharInputSpy_Create(fakeInput);
    }

    void teardown()
    {
      SortLines_Destroy();
      CharInputSpy_Destroy();
      FormatOutputSpy_Destroy();
      free(fakeInput);
    }

    void addFormatStringToFakeInput(const char * format, ...)
    {
      int writtenSize;
      va_list arguments;
      va_start(arguments, format);
      writtenSize = vsprintf(fakeInput + offset, format, arguments);

      offset += writtenSize;
      va_end(arguments);
    }

    void checkOutput(int expectedResult, char *expectedString)
    {
      LONGS_EQUAL(expectedResult, result);
      STRCMP_EQUAL(expectedString, FormatOutputSpy_GetOutput());
    }
};

TEST(SortLines, ParseNothing)
{
  char *fakeArgv[] = { "progname" };
  SortLines_ParseCommandline(1, fakeArgv);
  CHECK(!SortLines_IsNumeric());
}

TEST(SortLines, ParseNumeric)
{
  char *fakeArgv[] = { "progname", "-n" };
  SortLines_ParseCommandline(2, fakeArgv);
  CHECK(SortLines_IsNumeric());
}

TEST(SortLines, ParseReverse)
{
  char *fakeArgv[] = { "progname", "-r" };
  SortLines_ParseCommandline(2, fakeArgv);
  CHECK(SortLines_ShouldReverse());
}

TEST(SortLines, ParseFold)
{
  char *fakeArgv[] = { "progname", "-f" };
  SortLines_ParseCommandline(2, fakeArgv);
  CHECK(SortLines_ShouldFold());
}

TEST(SortLines, ParseDirectoryOption)
{
  char *fakeArgv[] = { "progname", "-d" };
  SortLines_ParseCommandline(2, fakeArgv);
  CHECK(SortLines_IsDirectoryOrder());
}

TEST(SortLines, ParseOneFieldOption)
{
  char *fakeArgv[] = { "progname", "-k2,2" };
  SortLines_ParseCommandline(2, fakeArgv);
  LONGS_EQUAL(2, SortLines_StartField());
  LONGS_EQUAL(2, SortLines_EndField());
}

TEST(SortLines, ParseOneFieldOptionFailedBeforeParsingFieldNumber)
{
  char *fakeArgv[] = { "progname", "-kn2,2" };
  SortLines_ParseCommandline(2, fakeArgv);
  STRCMP_EQUAL("sortLines: illegal field option n, expected integer\n",
               FormatOutputSpy_GetOutput());
}

TEST(SortLines, ParseOneFieldOptionFailedAfterParsingFieldNumber)
{
  char *fakeArgv[] = { "progname", "-k2,2n" };
  SortLines_ParseCommandline(2, fakeArgv);
  STRCMP_EQUAL("sortLines: illegal field option n, expected none\n",
               FormatOutputSpy_GetOutput());
}

TEST(SortLines, ParseOneFieldOptionWithOthers)
{
  char *fakeArgv[] = { "progname", "-k2nr,2" };
  SortLines_ParseCommandline(2, fakeArgv);
  CHECK(SortLines_IsNumeric());
  CHECK(SortLines_ShouldReverse());
  LONGS_EQUAL(2, SortLines_StartField());
  LONGS_EQUAL(2, SortLines_EndField());
}

TEST(SortLines, ParseMutlipleField)
{
  char *fakeArgv[] = { "progname", "-k2nr,2", "-k1f,1" };
  SortLines_ParseCommandline(3, fakeArgv);

  SortLines_SetFieldOption();

  CHECK(SortLines_IsNumeric());
  CHECK(SortLines_ShouldReverse());
  LONGS_EQUAL(2, SortLines_StartField());
  LONGS_EQUAL(2, SortLines_EndField());

  SortLines_NextFieldOption();

  CHECK(SortLines_ShouldFold());
  LONGS_EQUAL(1, SortLines_StartField());
  LONGS_EQUAL(1, SortLines_EndField());
}

TEST(SortLines, ParseNumericReverseCompoundForm)
{
  char *fakeArgv[] = { "progname", "-nr" };
  SortLines_ParseCommandline(2, fakeArgv);
  CHECK(SortLines_IsNumeric());
  CHECK(SortLines_ShouldReverse());
}

TEST(SortLines, ParseNumericReverseSeparateForm)
{
  char *fakeArgv[] = { "progname", "-n", "-r"};
  SortLines_ParseCommandline(3, fakeArgv);
  CHECK(SortLines_IsNumeric());
  CHECK(SortLines_ShouldReverse());
}

TEST(SortLines, ParseUnknownOption)
{
  char *fakeArgv[] = { "progname", "-x" };
  SortLines_ParseCommandline(2, fakeArgv);
  STRCMP_EQUAL("sortLines: unsupported option x\n",
               FormatOutputSpy_GetOutput());
}

TEST(SortLines, ParseUnknownCommand)
{
  char *fakeArgv[] = { "progname", "unknown" };
  SortLines_ParseCommandline(2, fakeArgv);
  STRCMP_EQUAL("Usage: sortLines -[k%d]drnf[,%d]\n",
               FormatOutputSpy_GetOutput());
}

TEST(SortLines, NumericCompare)
{
  LONGS_EQUAL(0, numcmp("8", "8"));
  LONGS_EQUAL(1, numcmp("100", "8"));
  LONGS_EQUAL(-1, numcmp("-8", "-4"));
}

TEST(SortLines, DoNothingWithNoInput)
{
  addFormatStringToFakeInput("");

  result = SortLines();

  checkOutput(0, "");
}

TEST(SortLines, CanSortOneLine)
{
  addFormatStringToFakeInput("One line does not need to be sorted.");

  result = SortLines();

  checkOutput(0, "One line does not need to be sorted.");
}

TEST(SortLines, CanSortMultilineUsingStrcmp)
{
  addFormatStringToFakeInput("Better than yesterday\n");
  addFormatStringToFakeInput("This line shoudn't be first.\n");
  addFormatStringToFakeInput("A head line is this!\n");
  addFormatStringToFakeInput("Cat vs Dog\n");

  char expectedOutput[] =
    "A head line is this!\n"
    "Better than yesterday\n"
    "Cat vs Dog\n"
    "This line shoudn't be first.\n";

  char *fakeArgv[] = { "progname" };
  SortLines_ParseCommandline(1, fakeArgv);

  result = SortLines();

  checkOutput(0, expectedOutput);
}

TEST(SortLines, CanSortMultilineUsingStrcmpReversed)
{
  addFormatStringToFakeInput("Better than yesterday\n");
  addFormatStringToFakeInput("This line shoudn't be first.\n");
  addFormatStringToFakeInput("A head line is this!\n");
  addFormatStringToFakeInput("Cat vs Dog\n");

  char expectedOutput[] =
    "This line shoudn't be first.\n"
    "Cat vs Dog\n"
    "Better than yesterday\n"
    "A head line is this!\n";

  char *fakeArgv[] = { "progname", "-r"};
  SortLines_ParseCommandline(2, fakeArgv);

  result = SortLines();

  checkOutput(0, expectedOutput);
}

TEST(SortLines, CanSortMultilineUsingStrcmpFolded)
{
  addFormatStringToFakeInput("better than yesterday\n");
  addFormatStringToFakeInput("this line shoudn't be first.\n");
  addFormatStringToFakeInput("A head line is this!\n");
  addFormatStringToFakeInput("Cat vs Dog\n");

  char expectedOutput[] =
    "A head line is this!\n"
    "better than yesterday\n"
    "Cat vs Dog\n"
    "this line shoudn't be first.\n";

  char *fakeArgv[] = { "progname", "-f" };
  SortLines_ParseCommandline(2, fakeArgv);

  result = SortLines();

  checkOutput(0, expectedOutput);
}

TEST(SortLines, CanSortMultilineUsingStrcmpInDirectoryOrder)
{
  addFormatStringToFakeInput("--better than yesterday\n");
  addFormatStringToFakeInput("__this line shoudn't be first.\n");
  addFormatStringToFakeInput("|_a head line is this!\n");
  addFormatStringToFakeInput("cat vs Dog\n");

  char expectedOutput[] =
    "|_a head line is this!\n"
    "--better than yesterday\n"
    "cat vs Dog\n"
    "__this line shoudn't be first.\n";

  char *fakeArgv[] = { "progname", "-d" };
  SortLines_ParseCommandline(2, fakeArgv);

  result = SortLines();

  checkOutput(0, expectedOutput);
}

TEST(SortLines, CanSortMultilineUsingStrcmpInDirectoryOrderWithFolding)
{
  addFormatStringToFakeInput("--Better than yesterday\n");
  addFormatStringToFakeInput("__This line shoudn't be first.\n");
  addFormatStringToFakeInput("|_a head line is this!\n");
  addFormatStringToFakeInput("cat vs Dog\n");

  char expectedOutput[] =
    "|_a head line is this!\n"
    "--Better than yesterday\n"
    "cat vs Dog\n"
    "__This line shoudn't be first.\n";

  char *fakeArgv[] = { "progname", "-df" };
  SortLines_ParseCommandline(2, fakeArgv);

  result = SortLines();

  checkOutput(0, expectedOutput);
}

TEST(SortLines, CanSortMultilineUsingNumcmp)
{
  addFormatStringToFakeInput("-4 Better than yesterday\n");
  addFormatStringToFakeInput("100 This line shoudn't be first.\n");
  addFormatStringToFakeInput("3 A head line is this!\n");
  addFormatStringToFakeInput("20 Cat vs Dog\n");

  char expectedOutput[] =
    "-4 Better than yesterday\n"
    "3 A head line is this!\n"
    "20 Cat vs Dog\n"
    "100 This line shoudn't be first.\n";

  char *fakeArgv[] = { "progname", "-n" };

  SortLines_ParseCommandline(2, fakeArgv);
  result = SortLines();

  checkOutput(0, expectedOutput);
}

TEST(SortLines, CanSortMultilineUsingNumcmpReversed)
{
  addFormatStringToFakeInput("-4 Better than yesterday\n");
  addFormatStringToFakeInput("100 This line shoudn't be first.\n");
  addFormatStringToFakeInput("3 A head line is this!\n");
  addFormatStringToFakeInput("20 Cat vs Dog\n");

  char expectedOutput[] =
    "100 This line shoudn't be first.\n"
    "20 Cat vs Dog\n"
    "3 A head line is this!\n"
    "-4 Better than yesterday\n";

  char *fakeArgv[] = { "progname", "-nr" };

  SortLines_ParseCommandline(2, fakeArgv);
  result = SortLines();

  checkOutput(0, expectedOutput);
}

TEST(SortLines, CanSortMultilineUsingNumcmpConfinedByFieldOption)
{
  addFormatStringToFakeInput("Better than -4 yesterday\n");
  addFormatStringToFakeInput("This line 100 shoudn't be first.\n");
  addFormatStringToFakeInput("A head 3 line is this!\n");
  addFormatStringToFakeInput("Cat vs 20 Dog\n");

  char expectedOutput[] =
    "Better than -4 yesterday\n"
    "A head 3 line is this!\n"
    "Cat vs 20 Dog\n"
    "This line 100 shoudn't be first.\n";

  char *fakeArgv[] = { "progname", "-k3n,3" };

  SortLines_ParseCommandline(2, fakeArgv);
  result = SortLines();

  checkOutput(0, expectedOutput);
}

TEST(SortLines, CanSortMultiFieldUsingDifferentComparator)
{
  addFormatStringToFakeInput("Field1: A Field2: 3 Field3: xx\n");
  addFormatStringToFakeInput("Field1: B Field2: 1 Field3: xx\n");
  addFormatStringToFakeInput("Field1: c Field2: 3 Field3: xx\n");
  addFormatStringToFakeInput("Field1: D Field2: 3 Field3: xx\n");

  char expectedOutput[] =
    "Field1: B Field2: 1 Field3: xx\n"
    "Field1: A Field2: 3 Field3: xx\n"
    "Field1: c Field2: 3 Field3: xx\n"
    "Field1: D Field2: 3 Field3: xx\n";

  char *fakeArgv[] = { "progname", "-k4n,4", "-k2f,2" };

  SortLines_ParseCommandline(3, fakeArgv);
  result = SortLines();

  checkOutput(0, expectedOutput);
}

TEST(SortLines, ReportErrorWhenOverflowed)
{
  for (int i = 0; i < MAXLINES + 1; ++i)
    addFormatStringToFakeInput("%d lines\n", i);

  result = SortLines();

  checkOutput(1, "input too big to sort\n");
}

TEST(SortLines, CanCopeWithFullCase)
{
  for (int i = 0; i < MAXLINES; ++i)
    addFormatStringToFakeInput("%d lines\n", i);

  char *fakeArgv[] = { "progname", "-n" };

  SortLines_ParseCommandline(2, fakeArgv);

  result = SortLines();

  checkOutput(0, fakeInput);
}
