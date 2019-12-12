#include "SortLines_internal.h"

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

static int compare(char *s1, char *s2)
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
static void setCompareProcedure(void)
{
    int i = 0;
    if (SortLines_StartField())
        preProcessors[i++] =
            chooseFieldFromRange(currentOptionp->startField,
                                 currentOptionp->endField);


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

    tieBreaker = optionsHead ? tieBreakUsingNextField : noTieBreak;
}
