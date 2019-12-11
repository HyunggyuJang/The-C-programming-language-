extern "C"
{
#include "Readlines.h"
#include "Getline.h"
#include "CharInputSpy.h"
#include "AllocSpy.h"
#include <stdio.h>
#include <memory.h>
#define MAXLINE 30
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Readlines)
{
    char characterInput[MAXLEN * MAXLINE];
    char *expectedLines[MAXLINE + 1];
    char *linePointers[MAXLINE];
    int nLines;
    int numberOfLines;
    void setup()
    {
        UT_PTR_SET(CharInput, CharInputSpy);
        UT_PTR_SET(charAlloc, AllocSpy_alloc);
        UT_PTR_SET(freeChar, AllocSpy_afree);
        areset();
        AllocSpy_Create();
        numberOfLines = 0;
        memset(characterInput, '\0', sizeof characterInput);
        memset(expectedLines, NULL, sizeof expectedLines);
        memset(linePointers, NULL, sizeof linePointers);
    }

    void teardown()
    {
        AllocSpy_Destroy();
        CharInputSpy_Destroy();
    }

    void setExpectedLine(char *oneLine)
    {
        expectedLines[numberOfLines++] = oneLine;
    }

    void setInputCharsFromExpectedLines()
    {
        for (int i = 0; i < numberOfLines; ++i)
            strcat(characterInput, expectedLines[i]);

        CharInputSpy_Create(characterInput);
    }

    void checkExpectedAndActual()
    {
        LONGS_EQUAL(numberOfLines, nLines);
        for (int i = 0; i < numberOfLines; ++i)
            STRCMP_EQUAL(expectedLines[i],
                         linePointers[i]);
        LONGS_EQUAL(strlen(characterInput) + nLines,
                    AllocSpy_AllocatedSpace());
    }
};

TEST(Readlines, NoAvailableLine)
{
    setExpectedLine("");

    setInputCharsFromExpectedLines();
    nLines = readlines(linePointers, MAXLINE);

    LONGS_EQUAL(0, nLines);
    for (int i = MAXLINE; i-- > 0;)
        POINTERS_EQUAL(NULL, linePointers[i]);
}

TEST(Readlines, OneAvailableLineAllocatable)
{
    setExpectedLine("One line is available.");

    setInputCharsFromExpectedLines();
    nLines = readlines(linePointers, MAXLINE);

    checkExpectedAndActual();
}

TEST(Readlines, OneAvailableLineButNoSpace)
{
    charAlloc(ALLOCSIZE);
    AllocSpy_Create();

    setExpectedLine("One line is available.");

    setInputCharsFromExpectedLines();
    nLines = readlines(linePointers, MAXLINE);

    LONGS_EQUAL(ERR, nLines);
    POINTERS_EQUAL(NULL, linePointers[0]);
    LONGS_EQUAL(0, AllocSpy_AllocatedSpace());
}

TEST(Readlines, MultipleLinesAvailableAndAllocatable)
{
    setExpectedLine("One line is available.\n");
    setExpectedLine("No actually it was two lines as whole.");

    setInputCharsFromExpectedLines();
    nLines = readlines(linePointers, MAXLINE);

    checkExpectedAndActual();
}

TEST(Readlines, MultipleLinesOverLimitation)
{
    for (int i; i < MAXLINE + 1; ++i)
        setExpectedLine("\n");

    setInputCharsFromExpectedLines();
    nLines = readlines(linePointers, MAXLINE);

    LONGS_EQUAL(ERR, nLines);
}

TEST(Readlines, MultipleLinesFull)
{
    for (int i; i < MAXLINE; ++i)
        setExpectedLine("Lines are full\n");

    setInputCharsFromExpectedLines();
    nLines = readlines(linePointers, MAXLINE);

    checkExpectedAndActual();
}
