#include "SortLines_compareSetter.h"
#include "SortLines.h"
#include "Readlines.h"
#include <stdlib.h>             /* atof */
#include <string.h>
#include <ctype.h>

static int (*compareProc)(char *s1, char *s2);
static void (*preProcessors[4])(char *to, char *from);
static int (*postProcessor)(int processed);
static int (*tieBreaker)(char *s1, char *s2);

static void preProcess(char *dest, char *source)
{
    int offset = 0;
    do
    {
        (preProcessors[offset])(dest, source);
        source = dest;
    } while (preProcessors[++offset]);
}

int compare(char *s1, char *s2)
{
    static char localS1[MAXLEN];
    static char localS2[MAXLEN];

    preProcess(localS1, s1);
    preProcess(localS2, s2);

    int resultValue =  postProcessor(compareProc(localS1, localS2));
    if (resultValue)
        return resultValue;
    else
        return tieBreaker(s1, s2);
}

int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    if (v1 > v2)
        return 1;
    return 0;
}

/* toLowers ADT */
static void toLowers(char *destination, char *source)
{
    while ((*destination++ = tolower(*source++)))
        ;
}

/* chooseFieldADT */
static int startField;
static int endField;

static void chooseField(char *destination, char *source)
{
    int tStartField = startField;
    int endOffset = endField - startField;
    for (; isspace(*source); ++source)
        ;
    while (--tStartField > 0)
    {
        while (!isspace(*source++))
            ;
        for (; isspace(*source); ++source)
            ;
    }
    if (endOffset < 0)
        strcpy(destination, source);
    do
    {
        while (!isspace(*source))
            *destination++ = *source++;
        for (;isspace(*source); ++source)
            ;
        if (endOffset)
            *destination++ = ' ';
        *destination = '\0';
    }
    while (--endOffset >= 0);
}

static void (*chooseFieldFromRange(int startingField, int endingField))(char *, char *)
{
    startField = startingField;
    endField = endingField;
    return chooseField;
}

/* toDirectoryCharsADT */
static void toDirectoryChars(char *destination, char *source)
{
    for (; *source; ++source)
        if (isalnum(*source) || *source == ' ')
            *destination++ = *source;
    *destination = '\0';
}

/* postProcessor functions */
static int invertOutput(int processed)
{
    return -processed;
}

static int idendity(int processed)
{
    return processed;
}

/* tieBreaker functions */
static int tieBreakUsingNextField(char *s1, char *s2)
{
    if (!SortLines_HaveNextFieldOption())
    {
        SortLines_SetFieldOption();
        return 0;
    }
    SortLines_NextFieldOption();
    setCompareProcedure();
    return compare(s1, s2);
}

static int noTieBreak(char *s1, char *s2)
{
    return 0;
}

void setCompareProcedure(void)
{
    int i = 0;
    if (SortLines_StartField())
        preProcessors[i++] =
            chooseFieldFromRange(SortLines_StartField(),
                                 SortLines_EndField());

    if (SortLines_IsDirectoryOrder())
        preProcessors[i++] = toDirectoryChars;

    if (SortLines_ShouldFold())
        preProcessors[i++] = toLowers;

    if (i)
        preProcessors[i] = 0;
    else
    {
        preProcessors[0] = (void (*)(char *, char *)) strcpy;
        preProcessors[1] = 0;
    }

    compareProc = SortLines_IsNumeric() ? numcmp : (int (*)(char *, char *))strcmp;

    postProcessor = SortLines_ShouldReverse() ? invertOutput : idendity;

    tieBreaker = FieldOption_IsCreated() ? tieBreakUsingNextField : noTieBreak;
}
